#include "dz1_asn1_codecTest.h"

static u8_t sample_data[] = 
{ 
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' 
};
static u32_t sample_data_len = sizeof(sample_data);

static GASN_DEC_DECLARE(ObjectDescriptor, dz1_objdescr_ber_dec_gasn)
static GASN_ENC_DECLARE(ObjectDescriptor, dz1_objdescr_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(ObjectDescriptor, dz1_objdescr_dump_gasn, v)

static int _objdescr_cmp(ObjectDescriptor *a, Dz1Asn1ObjDescr *b)
{
	return _string_cmp(a, b);
}

static bool_t _objdescr_imp_test(Dz1Error *errp)
{
	ObjectDescriptor *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (ObjectDescriptor *)mpool_calloc(ws.Pmemory, sizeof(ObjectDescriptor), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_ObjectDescriptor(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrObjDescr, v, dz1_objdescr_ber_enc_gasn, dz1_objdescr_dump_gasn, _objdescr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _objdescr_exp_test(Dz1Error *errp)
{
	Dz1Asn1ObjDescr *v = Dz1Asn1ObjDescr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1ObjDescr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrObjDescr, v, dz1_objdescr_ber_dec_gasn, dz1_objdescr_dump_gasn, _objdescr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1ObjDescr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _objdescr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x27, 0x80, 
			0x07, 0x02, 'A', 'B',
			0x07, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x27, 0x0E, 
			0x07, 0x02, 'A', 'B',									// 4
			0x07, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrObjDescr, &ber_def, dz1_objdescr_ber_dec_gasn, dz1_objdescr_dump_gasn, _objdescr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrObjDescr, &ber_indef, dz1_objdescr_ber_dec_gasn, dz1_objdescr_dump_gasn, _objdescr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _objdescr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("OBJECT DESCRIPTOR Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_objdescr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_objdescr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_objdescr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// ObjectDescriptor Import Test
static void cmd_ber_imp_objdescr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_objdescr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_objdescr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_objdescr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_objdescr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_objdescr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_objdescr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_objdescr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("objdescr"));
	if (argc < 2) cmd_ber_imp_objdescr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_objdescr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_objdescr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_objdescr_usage(argv[0]);
	}
}
// ObjectDescriptor Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ObjectDescriptor Export Test
static void cmd_ber_exp_objdescr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_objdescr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("objdescr"));
	if (argc != 1) cmd_ber_exp_objdescr_usage(n);
	else
	{
		// Command Code Here
	}
}
// ObjectDescriptor Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static u8_t digit_data[] = 
{ 
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};
static u32_t digit_data_len = sizeof(digit_data);

static GASN_DEC_DECLARE(NumericString, dz1_digitstr_ber_dec_gasn)
static GASN_ENC_DECLARE(NumericString, dz1_digitstr_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(NumericString, dz1_digitstr_dump_gasn, v)

static int _digitstr_cmp(NumericString *a, Dz1Asn1DigitStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _digitstr_imp_test(Dz1Error *errp)
{
	NumericString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (NumericString *)mpool_calloc(ws.Pmemory, sizeof(NumericString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_NumericString(&ws, v, digit_data, digit_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrDigitStr, v, dz1_digitstr_ber_enc_gasn, dz1_digitstr_dump_gasn, _digitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _digitstr_exp_test(Dz1Error *errp)
{
	Dz1Asn1DigitStr *v = Dz1Asn1DigitStr_new(digit_data, digit_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1DigitStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrDigitStr, v, dz1_digitstr_ber_dec_gasn, dz1_digitstr_dump_gasn, _digitstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1DigitStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _digitstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x32, 0x80, 
			0x12, 0x02, '1', '2',
			0x12, 0x08, '3', '4', '5', '6', '7', '8', '9', '0',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x32, 0x0E, 
			0x12, 0x02, '1', '2',									// 4
			0x12, 0x08, '3', '4', '5', '6', '7', '8', '9', '0',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrDigitStr, &ber_def, dz1_digitstr_ber_dec_gasn, dz1_digitstr_dump_gasn, _digitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrDigitStr, &ber_indef, dz1_digitstr_ber_dec_gasn, dz1_digitstr_dump_gasn, _digitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _digitstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("DigitString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_digitstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_digitstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_digitstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// DigitString Import Test
static void cmd_ber_imp_digitstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_digitstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_objdescr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_digitstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_digitstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_digitstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_digitstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_digitstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("digitstr"));
	if (argc < 2) cmd_ber_imp_digitstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_digitstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_digitstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_digitstr_usage(argv[0]);
	}
}
// DigitString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// DigitString Export Test
static void cmd_ber_exp_digitstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_digitstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("digitstr"));
	if (argc != 1) cmd_ber_exp_digitstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// DigitString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(PrintableString, dz1_printstring_ber_dec_gasn)
static GASN_ENC_DECLARE(PrintableString, dz1_printstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(PrintableString, dz1_printstring_dump_gasn, v)

static int _printstr_cmp(PrintableString *a, Dz1Asn1PrintStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _printstr_imp_test(Dz1Error *errp)
{
	PrintableString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (PrintableString *)mpool_calloc(ws.Pmemory, sizeof(PrintableString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_PrintableString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrPrintStr, v, dz1_printstring_ber_enc_gasn, dz1_printstring_dump_gasn, _printstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _printstr_exp_test(Dz1Error *errp)
{
	Dz1Asn1PrintStr *v = Dz1Asn1PrintStr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1PrintStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrPrintStr, v, dz1_printstring_ber_dec_gasn, dz1_printstring_dump_gasn, _printstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1PrintStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _printstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x33, 0x80, 
			0x13, 0x02, 'A', 'B',
			0x13, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x33, 0x0E, 
			0x13, 0x02, 'A', 'B',									// 4
			0x13, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrPrintStr, &ber_def, dz1_printstring_ber_dec_gasn, dz1_printstring_dump_gasn, _printstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrPrintStr, &ber_indef, dz1_printstring_ber_dec_gasn, dz1_printstring_dump_gasn, _printstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _printstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("PrintableString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_printstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_printstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_printstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// PrintableString Import Test
static void cmd_ber_imp_printstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_printstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_printstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_printstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_printstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_printstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_printstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_printstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("printstr"));
	if (argc < 2) cmd_ber_imp_printstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_printstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_printstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_printstr_usage(argv[0]);
	}
}
// PrintableString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PrintableString Export Test
static void cmd_ber_exp_printstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_printstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("printstr"));
	if (argc != 1) cmd_ber_exp_printstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// PrintableString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(TeletexString, dz1_teletexstring_ber_dec_gasn)
static GASN_ENC_DECLARE(TeletexString, dz1_teletexstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(TeletexString, dz1_teletexstring_dump_gasn, v)

static int _teletexstr_cmp(TeletexString *a, Dz1Asn1TeletexStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _teletexstr_imp_test(Dz1Error *errp)
{
	TeletexString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (TeletexString *)mpool_calloc(ws.Pmemory, sizeof(TeletexString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_TeletexString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrTeletexStr, v, dz1_teletexstring_ber_enc_gasn, dz1_teletexstring_dump_gasn, _teletexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _teletexstr_exp_test(Dz1Error *errp)
{
	Dz1Asn1TeletexStr *v = Dz1Asn1TeletexStr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1TeletexStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrTeletexStr, v, dz1_teletexstring_ber_dec_gasn, dz1_teletexstring_dump_gasn, _teletexstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1TeletexStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _teletexstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x34, 0x80, 
			0x14, 0x02, 'A', 'B',
			0x14, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x34, 0x0E, 
			0x14, 0x02, 'A', 'B',									// 4
			0x14, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrTeletexStr, &ber_def, dz1_teletexstring_ber_dec_gasn, dz1_teletexstring_dump_gasn, _teletexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrTeletexStr, &ber_indef, dz1_teletexstring_ber_dec_gasn, dz1_teletexstring_dump_gasn, _teletexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _teletexstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("TeletexString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_teletexstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_teletexstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_teletexstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// TeletexString Import Test
static void cmd_ber_imp_teletexstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_teletexstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_teletexstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_teletexstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_teletexstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_teletexstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_teletexstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_teletexstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("teletexstr"));
	if (argc < 2) cmd_ber_imp_teletexstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_teletexstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_teletexstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_teletexstr_usage(argv[0]);
	}
}
// TeletexString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TeletexString Export Test
static void cmd_ber_exp_teletexstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_teletexstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("teletexstr"));
	if (argc != 1) cmd_ber_exp_teletexstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// TeletexString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(VideotexString, dz1_videotexstring_ber_dec_gasn)
static GASN_ENC_DECLARE(VideotexString, dz1_videotexstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(VideotexString, dz1_videotexstring_dump_gasn, v)

static int _videotexstr_cmp(VideotexString *a, Dz1Asn1VideotexStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _videotexstr_imp_test(Dz1Error *errp)
{
	VideotexString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (VideotexString *)mpool_calloc(ws.Pmemory, sizeof(VideotexString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_VideotexString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrVideotexStr, v, dz1_videotexstring_ber_enc_gasn, dz1_videotexstring_dump_gasn, _videotexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _videotexstr_exp_test(Dz1Error *errp)
{
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _videotexstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x35, 0x80, 
			0x15, 0x02, 'A', 'B',
			0x15, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x35, 0x0E, 
			0x15, 0x02, 'A', 'B',									// 4
			0x15, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrVideotexStr, &ber_def, dz1_videotexstring_ber_dec_gasn, dz1_videotexstring_dump_gasn, _videotexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrVideotexStr, &ber_indef, dz1_videotexstring_ber_dec_gasn, dz1_videotexstring_dump_gasn, _videotexstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _videotexstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("VideotexString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_videotexstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_videotexstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_videotexstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// VideotexString Import Test
static void cmd_ber_imp_videotexstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_videotexstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_videotexstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_videotexstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_videotexstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_videotexstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_videotexstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_videotexstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("videotexstr"));
	if (argc < 2) cmd_ber_imp_videotexstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_videotexstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_videotexstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_videotexstr_usage(argv[0]);
	}
}
// VideotexString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VideotexString Export Test
static void cmd_ber_exp_videotexstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_videotexstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("videotexstr"));
	if (argc != 1) cmd_ber_exp_videotexstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// VideotexString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(IA5String, dz1_ia5string_ber_dec_gasn)
static GASN_ENC_DECLARE(IA5String, dz1_ia5string_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(IA5String, dz1_ia5string_dump_gasn, v)

static int _ia5str_cmp(IA5String *a, Dz1Asn1IA5Str *b)
{
	return _string_cmp(a, b);
}

static bool_t _ia5str_imp_test(Dz1Error *errp)
{
	IA5String *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (IA5String *)mpool_calloc(ws.Pmemory, sizeof(IA5String), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_IA5String(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrIA5Str, v, dz1_ia5string_ber_enc_gasn, dz1_ia5string_dump_gasn, _ia5str_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _ia5str_exp_test(Dz1Error *errp)
{
	Dz1Asn1IA5Str *v = Dz1Asn1IA5Str_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1IA5Str_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrIA5Str, v, dz1_ia5string_ber_dec_gasn, dz1_ia5string_dump_gasn, _ia5str_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1IA5Str_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _ia5str_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x36, 0x80, 
			0x16, 0x02, 'A', 'B',
			0x16, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x36, 0x0E, 
			0x16, 0x02, 'A', 'B',									// 4
			0x16, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrIA5Str, &ber_def, dz1_ia5string_ber_dec_gasn, dz1_ia5string_dump_gasn, _ia5str_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrIA5Str, &ber_indef, dz1_ia5string_ber_dec_gasn, dz1_ia5string_dump_gasn, _ia5str_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _ia5str_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("IA5String Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_ia5str_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_ia5str_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_ia5str_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
/*
////////////////////////////////////////////////////////////////////////////////
// IA5String Import Test
static void cmd_ber_imp_ia5str1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_ia5str1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_ia5str1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_ia5str2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_ia5str2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_ia5str2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_ia5str_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_ia5str(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("ia5string"));
	if (argc < 2) cmd_ber_imp_ia5str_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_ia5str1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_ia5str2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_ia5str_usage(argv[0]);
	}
}
// IA5String Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// IA5String Export Test
static void cmd_ber_exp_ia5str_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_ia5str(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("ia5str"));
	if (argc != 1) cmd_ber_exp_ia5str_usage(n);
	else
	{
		// Command Code Here
	}
}
// IA5String Export Test
////////////////////////////////////////////////////////////////////////////////
*/
static GASN_DEC_DECLARE(GraphicString, dz1_graphicstring_ber_dec_gasn)
static GASN_ENC_DECLARE(GraphicString, dz1_graphicstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(GraphicString, dz1_graphicstring_dump_gasn, v)

static int _graphicstr_cmp(GraphicString *a, Dz1Asn1GraphicStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _graphicstr_imp_test(Dz1Error *errp)
{
	GraphicString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (GraphicString *)mpool_calloc(ws.Pmemory, sizeof(GraphicString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_GraphicString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrGraphicStr, v, dz1_graphicstring_ber_enc_gasn, dz1_graphicstring_dump_gasn, _graphicstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _graphicstr_exp_test(Dz1Error *errp)
{
	Dz1Asn1GraphicStr *v = Dz1Asn1GraphicStr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1GraphicStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrGraphicStr, v, dz1_graphicstring_ber_dec_gasn, dz1_graphicstring_dump_gasn, _graphicstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1GraphicStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _graphicstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x39, 0x80, 
			0x19, 0x02, 'A', 'B',
			0x19, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x39, 0x0E, 
			0x19, 0x02, 'A', 'B',									// 4
			0x19, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrGraphicStr, &ber_def, dz1_graphicstring_ber_dec_gasn, dz1_graphicstring_dump_gasn, _graphicstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrGraphicStr, &ber_indef, dz1_graphicstring_ber_dec_gasn, dz1_graphicstring_dump_gasn, _graphicstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);;
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _graphicstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("GraphicString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_graphicstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_graphicstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_graphicstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// GraphicString Import Test
static void cmd_ber_imp_graphicstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_graphicstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_graphicstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_graphicstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_graphicstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_graphicstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_graphicstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_graphicstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("graphicstr"));
	if (argc < 2) cmd_ber_imp_graphicstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_graphicstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_graphicstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_graphicstr_usage(argv[0]);
	}
}
// GraphicString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GraphicString Export Test
static void cmd_ber_exp_graphicstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_graphicstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("graphicstr"));
	if (argc != 1) cmd_ber_exp_graphicstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// GraphicString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(VisibleString, dz1_visiblestring_ber_dec_gasn)
static GASN_ENC_DECLARE(VisibleString, dz1_visiblestring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(VisibleString, dz1_visiblestring_dump_gasn, v)

static int _visiblestr_cmp(VisibleString *a, Dz1Asn1VisibleStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _visiblestr_imp_test(Dz1Error *errp)
{
	VisibleString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (VisibleString *)mpool_calloc(ws.Pmemory, sizeof(VisibleString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_VisibleString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrVisibleStr, v, dz1_visiblestring_ber_enc_gasn, dz1_visiblestring_dump_gasn, _visiblestr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _visiblestr_exp_test(Dz1Error *errp)
{
	Dz1Asn1VisibleStr *v = Dz1Asn1VisibleStr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1VisibleStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrVisibleStr, v, dz1_visiblestring_ber_dec_gasn, dz1_visiblestring_dump_gasn, _visiblestr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1VisibleStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _visiblestr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x3A, 0x80, 
			0x1A, 0x02, 'A', 'B',
			0x1A, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x3A, 0x0E, 
			0x1A, 0x02, 'A', 'B',									// 4
			0x1A, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrVisibleStr, &ber_def, dz1_visiblestring_ber_dec_gasn, dz1_visiblestring_dump_gasn, _visiblestr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrVisibleStr, &ber_indef, dz1_visiblestring_ber_dec_gasn, dz1_visiblestring_dump_gasn, _visiblestr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _visiblestr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("VisibleString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_visiblestr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_visiblestr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_visiblestr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// VisibleString Import Test
static void cmd_ber_imp_visiblestr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_visiblestr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_visiblestr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_visiblestr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_visiblestr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_visiblestr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_visiblestr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_visiblestr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("visiblestr"));
	if (argc < 2) cmd_ber_imp_visiblestr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_visiblestr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_visiblestr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_visiblestr_usage(argv[0]);
	}
}
// VisibleString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// VisibleString Export Test
static void cmd_ber_exp_visiblestr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_visiblestr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("visiblestr"));
	if (argc != 1) cmd_ber_exp_visiblestr_usage(n);
	else
	{
		// Command Code Here
	}
}
// VisibleString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(GeneralString, dz1_generalstring_ber_dec_gasn)
static GASN_ENC_DECLARE(GeneralString, dz1_generalstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(GeneralString, dz1_generalstring_dump_gasn, v)

static int _generalstr_cmp(GeneralString *a, Dz1Asn1GeneralStr *b)
{
	return _string_cmp(a, b);
}

static bool_t _generalstr_imp_test(Dz1Error *errp)
{
	GeneralString *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (GeneralString *)mpool_calloc(ws.Pmemory, sizeof(GeneralString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_GeneralString(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrGeneralStr, v, dz1_generalstring_ber_enc_gasn, dz1_generalstring_dump_gasn, _generalstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generalstr_exp_test(Dz1Error *errp)
{
	Dz1Asn1GeneralStr *v = Dz1Asn1GeneralStr_new(sample_data, sample_data_len, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1GeneralStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrGeneralStr, v, dz1_generalstring_ber_dec_gasn, dz1_generalstring_dump_gasn, _generalstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1GeneralStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generalstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x3B, 0x80, 
			0x1B, 0x02, 'A', 'B',
			0x1B, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x3B, 0x0E, 
			0x1B, 0x02, 'A', 'B',									// 4
			0x1B, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrGeneralStr, &ber_def, dz1_generalstring_ber_dec_gasn, dz1_generalstring_dump_gasn, _generalstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrGeneralStr, &ber_indef, dz1_generalstring_ber_dec_gasn, dz1_generalstring_dump_gasn, _generalstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generalstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("GeneralString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_generalstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_generalstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_generalstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// GeneralString Import Test
static void cmd_ber_imp_generalstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_generalstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_generalstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_generalstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_generalstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_generalstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_generalstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_generalstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("generalstr"));
	if (argc < 2) cmd_ber_imp_generalstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_generalstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_generalstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_generalstr_usage(argv[0]);
	}
}
// GeneralString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GeneralString Export Test
static void cmd_ber_exp_generalstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_generalstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("generalstr"));
	if (argc != 1) cmd_ber_exp_generalstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// GeneralString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////////////////////////
// String Import Test
static void cmd_ber_imp_string_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <objdescr | digitstr | printstr | teletesxtr | videotexstr | ia5str | graphicstr | visiblestr | generalstr> <params...>\n"), n); }
void cmd_ber_imp_string(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("string"));
	if (argc < 2) cmd_ber_imp_string_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("objdescr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("o")) == 0) cmd_ber_imp_objdescr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("digitstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("d")) == 0) cmd_ber_imp_digitstr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("printstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_printstr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("teletexstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("t")) == 0) cmd_ber_imp_teletexstr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("videotexstr")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("v")) == 0) cmd_ber_imp_videotexstr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("ia5str")) == 0			|| Dz1STRCMP(argv[1], Dz1Text("i")) == 0) cmd_ber_imp_ia5str(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("graphicstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("g")) == 0) cmd_ber_imp_graphicstr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("visiblestr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("s")) == 0) cmd_ber_imp_visiblestr(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("generalstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("x")) == 0) cmd_ber_imp_generalstr(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_string_usage(argv[0]);
	}
}
// String Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// String Export Test
static void cmd_ber_simple_string_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <objdescr | digitstr | printstr | teletesxtr | videotexstr | ia5str | graphicstr | visiblestr(s) | generalstr(x) | all>\n"), n); }
void cmd_ber_simple_string(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("string"));
	if (argc != 2) cmd_ber_simple_string_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("objdescr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("o")) == 0)	// 7
		{
			if (_objdescr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("digitstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("d")) == 0)	// 18
		{
			if (_digitstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("printstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("p")) == 0)	// 19
		{
			if (_printstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("teletexstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("t")) == 0)	// 20
		{
			if (_teletexstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("videotexstr")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("v")) == 0)	// 21
		{
			if (_videotexstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("ia5str")) == 0			|| Dz1STRCMP(argv[1], Dz1Text("i")) == 0)	// 22
		{
			if (_ia5str_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("graphicstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("g")) == 0)	// 25
		{
			if (_graphicstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("visiblestr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("s")) == 0)	// 26
		{
			if (_visiblestr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("generalstr")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("x")) == 0)	// 27
		{
			if (_generalstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_objdescr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_digitstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_printstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_teletexstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_videotexstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_ia5str_test(errp) == FALSE) ERR_OUT(errp);
			else if (_graphicstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_visiblestr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_generalstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_string_usage(argv[0]);
	}
}
// String Export Test
////////////////////////////////////////////////////////////////////////////////

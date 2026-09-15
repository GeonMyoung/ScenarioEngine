#include "dz1_asn1_codecTest.h"

static u8_t sample_data[] = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };

////////////////////////////////////////////////////////////////////////////////
// BITSTRING Import Test
static GASN_DEC_DECLARE(BITSTRING, dz1_bitstring_ber_dec_gasn)
static GASN_ENC_DECLARE(BITSTRING, dz1_bitstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(BITSTRING, dz1_bitstring_dump_gasn, v)

static int _bitstr_cmp(BITSTRING *gasn_ptr, Dz1Asn1BitStr *dz1asn_ptr)
{
	if (gasn_ptr->numbits < dz1asn_ptr->maxBit) return -1;
	else if (gasn_ptr->numbits > dz1asn_ptr->maxBit) return 1;
	else if (gasn_ptr->numbits == 0) return 0;
	else
	{
		int status = 0;
		u32_t byte_len = (gasn_ptr->numbits / 8) + ((gasn_ptr->numbits % 8) ? 1 : 0);
		if ((status = memcmp(gasn_ptr->data, dz1asn_ptr->bits, byte_len - 1)) != 0) return status;
		else
		{
			int last_byte_usage = gasn_ptr->numbits % 8;
			int shf = 8 - last_byte_usage;
			u8_t mask = ~((0x01 << shf) - 1);
			u8_t _a = gasn_ptr->data[byte_len - 1] & mask, _b = dz1asn_ptr->bits[byte_len - 1] & mask;
			if (_a < _b) return -1;
			else if (_a > _b) return 1;
			else return 0;
		}
	}
}

static bool_t _bitstr_imp_test(Dz1Error *errp)
{
	u32_t bits_len = sizeof(sample_data) * 8 - 4;

	BITSTRING *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (BITSTRING *)mpool_calloc(ws.Pmemory, sizeof(BITSTRING), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_BITSTRING(&ws, v, sample_data, bits_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrBitStr, v, dz1_bitstring_ber_enc_gasn, dz1_bitstring_dump_gasn, _bitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf(Dz1T("Test Success\n"));
		Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bitstr_exp_test(Dz1Error *errp)
{
	u32_t bits_len = sizeof(sample_data) * 8 - 4;

	Dz1Asn1BitStr *v = Dz1Asn1BitStr_new(sample_data, sizeof(sample_data), errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1BitStr_delAndSetNull, (void *)&v);
		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrBitStr, v, dz1_bitstring_ber_dec_gasn, dz1_bitstring_dump_gasn, _bitstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Asn1BitStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bitstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x23, 0x80, 
			0x03, 0x03, 0x00, 0xFF, 0xFF,										// 5
			0x03, 0x09, 0x04, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,	// 11
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x23, 0x10, 
			0x03, 0x03, 0x00, 0xFF, 0xFF,										// 5
			0x03, 0x09, 0x04, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10	// 11
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrBitStr, &ber_def, dz1_bitstring_ber_dec_gasn, dz1_bitstring_dump_gasn, _bitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrBitStr, &ber_indef, dz1_bitstring_ber_dec_gasn, dz1_bitstring_dump_gasn, _bitstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bitstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("BIT STRING Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_bitstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_bitstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_bitstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
static void cmd_ber_imp_bitstring1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_bitstring1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_bitstring1_usage(n);
	else
	{
		// Command Code Here
	}
}
*/

/*
static void cmd_ber_imp_bitstring2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_bitstring2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_bitstring2_usage(n);
	else
	{
		// Command Code Here
	}
}
static void cmd_ber_imp_bitstring_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_bitstring(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("bitstring"));
	if (argc < 2) cmd_ber_imp_bitstring_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_bitstring1(ptr, n, argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_bitstring2(ptr, n, argc-1, &argv[1]);
		else cmd_ber_imp_bitstring_usage(argv[0]);
	}
}
*/
// BITSTRING Import Test
////////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////////////////////////
// BITSTRING Export Test
static void cmd_ber_exp_bitstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_bitstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("bitstring"));
	if (argc != 1) cmd_ber_exp_bitstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// BITSTRING Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(OCTETSTRING, dz1_octetstring_ber_dec_gasn)
static GASN_ENC_DECLARE(OCTETSTRING, dz1_octetstring_ber_enc_gasn)
static GASN_DUMP_TAB_DECLARE(OCTETSTRING, dz1_octetstring_dump_gasn, v)

static bool_t _octetstr_imp_test(Dz1Error *errp)
{
	u32_t len = sizeof(sample_data);

	OCTETSTRING *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (OCTETSTRING *)mpool_calloc(ws.Pmemory, sizeof(OCTETSTRING), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_OCTETSTRING(&ws, v, sample_data, len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrOctetStr, v, dz1_octetstring_ber_enc_gasn, dz1_octetstring_dump_gasn, _octetstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else
	{
		Dz1Thread_printf(Dz1T("Test Success\n"));
		Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _octetstr_exp_test(Dz1Error *errp)
{
	u32_t sample_len = sizeof(sample_data);
	Dz1Asn1OctetStr *dz1asn = Dz1Asn1OctetStr_new(sample_data, sample_len, errp);
	if (dz1asn == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1BitStr_delAndSetNull, (void *)&dz1asn);
		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrOctetStr, dz1asn, dz1_octetstring_ber_dec_gasn, dz1_octetstring_dump_gasn, _octetstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Asn1BitStr_delAndSetNull, (void *)&dz1asn);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _octetstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x24, 0x80, 
			0x04, 0x02, 0xFF, 0xFF,
			0x04, 0x08, 0xFE, 0xDC, 0xBA, 0x98,0x76, 0x54, 0x32, 0x10,
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x24, 0x0E, 
			0x04, 0x02, 0xFF, 0xFF,											// 4
			0x04, 0x08, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10,		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrOctetStr, &ber_def, dz1_octetstring_ber_dec_gasn, dz1_octetstring_dump_gasn, _octetstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrOctetStr, &ber_indef, dz1_octetstring_ber_dec_gasn, dz1_octetstring_dump_gasn, _octetstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _octetstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("OCTET STRING Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_octetstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_octetstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_octetstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// OCTET STRING Import Test

static void cmd_ber_imp_octetstring1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_octetstring1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_octetstring1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_octetstring2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_octetstring2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_octetstring2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_octetstring_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_octetstring(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("octetstring"));
	if (argc < 2) cmd_ber_imp_octetstring_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_octetstring1(ptr, n, argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_octetstring2(ptr, n, argc-1, &argv[1]);
		else cmd_ber_imp_octetstring_usage(argv[0]);
	}
}
// OCTET STRING Import Test
////////////////////////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////////////////////////
// OCTET STRING Export Test
static void cmd_ber_exp_octetstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_octetstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("octetstr"));
	if (argc != 1) cmd_ber_exp_bitstr_usage(n);
	else
	{
		// Command Code Here
	}
}
// OCTET STRING Export Test
////////////////////////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////////////////////////
// Binary Import Test
static void cmd_ber_imp_binary_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <bitstring | octetstring>\n"), n); }
void cmd_ber_imp_binary(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("binary"));
	if (argc < 2) cmd_ber_imp_binary_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("bitstring")) == 0 || Dz1STRCMP(argv[1], Dz1Text("b")) == 0) cmd_ber_imp_bitstring(ptr, n, argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("octetstring")) == 0 || Dz1STRCMP(argv[1], Dz1Text("o")) == 0) cmd_ber_imp_octetstring(ptr, n, argc-1, &argv[1]);
		else cmd_ber_imp_binary_usage(argv[0]);
	}
}
// Binary Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// Binary Export Test
static void cmd_ber_simple_binary_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <bitstring | octetstring | all>\n"), n); }
void cmd_ber_simple_binary(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("binary"));
	if (argc != 2) cmd_ber_simple_binary_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("bitstring")) == 0 || Dz1STRCMP(argv[1], Dz1Text("b")) == 0)	// 3
		{
			if (_bitstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("octetstring")) == 0 || Dz1STRCMP(argv[1], Dz1Text("o")) == 0)	// 4
		{
			if (_octetstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0 || Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_bitstr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_octetstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_binary_usage(argv[0]);
	}
}
// Binary Test
////////////////////////////////////////////////////////////////////////////////

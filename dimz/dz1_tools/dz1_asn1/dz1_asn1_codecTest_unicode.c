#include "dz1_asn1_codecTest.h"

#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
#define GASN_LIB_UNIVERSAL_CHARSET			"UCS-4LE"
#define GASN_LIB_BMP_CHARSET				"UCS-2LE"
#elif DZ1_ENDIAN == DZ1_ENDIAN_BIG
#define GASN_LIB_UNIVERSAL_CHARSET			"UCS-4BE"
#define GASN_LIB_BMP_CHARSET				"UCS-2BE"
#else
#error Endian not defined
#endif

static u8_t sample_data[] = 
{ 
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' 
};
static u32_t sample_data_len = sizeof(sample_data);

static GASN_DEC_DECLARE(UTF8Str, dz1_utf8string_ber_dec_gasn)
static GASN_ENC_DECLARE(UTF8Str, dz1_utf8string_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(UTF8Str, dz1_utf8string_dump_gasn, v)

static int _utf8str_cmp(UTF8Str *a, Dz1Asn1UTF8Str *b)
{
	return _string_cmp(a, b);
}

static bool_t _utf8str_imp_test(Dz1Error *errp)
{
	UTF8Str *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (UTF8Str *)mpool_calloc(ws.Pmemory, sizeof(UTF8Str), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_UTF8Str(&ws, v, sample_data, sample_data_len) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrUTF8Str, v, dz1_utf8string_ber_enc_gasn, dz1_utf8string_dump_gasn, _utf8str_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _utf8str_exp_test(Dz1Error *errp)
{
	Dz1Asn1UTF8Str *v = Dz1Asn1UTF8Str_newFromBuf(sample_data, sample_data_len, "ASCII", errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTF8Str_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrUTF8Str, v, dz1_utf8string_ber_dec_gasn, dz1_utf8string_dump_gasn, _utf8str_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1UTF8Str_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _utf8str_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x2C, 0x80, 
			0x0C, 0x02, 'A', 'B',
			0x0C, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x2C, 0x0E, 
			0x0C, 0x02, 'A', 'B',									// 4
			0x0C, 0x08, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',		// 10
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrUTF8Str, &ber_def, dz1_utf8string_ber_dec_gasn, dz1_utf8string_dump_gasn, _utf8str_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrUTF8Str, &ber_indef, dz1_utf8string_ber_dec_gasn, dz1_utf8string_dump_gasn, _utf8str_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _utf8str_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("UTF8String Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_utf8str_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_utf8str_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_utf8str_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// UTF8Str Import Test
static void cmd_ber_imp_utf8str1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_utf8str1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_utf8str1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_utf8str2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_utf8str2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_utf8str2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_utf8str_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_utf8str(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("utf8str"));
	if (argc < 2) cmd_ber_imp_utf8str_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_utf8str1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_utf8str2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_utf8str_usage(argv[0]);
	}
}
// UTF8Str Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UTF8Str Export Test
static void cmd_ber_exp_utf8str_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_utf8str(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("utf8str"));
	if (argc != 1) cmd_ber_exp_utf8str_usage(n);
	else
	{
		// Command Code Here
	}
}
// UTF8Str Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(UniversalString, dz1_unistring_ber_dec_gasn)
static GASN_ENC_DECLARE(UniversalString, dz1_unistring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(UniversalString, dz1_unistring_dump_gasn, v)

static int _unistr_cmp(UniversalString *gasn_ptr, Dz1Asn1UniversalStr *dz1_asn1_ptr)
{
	u32_t a_cnt = gasn_ptr->nchar, b_cnt = dz1_asn1_ptr->size / 4;
	if (a_cnt < b_cnt) return -1;
	else if (a_cnt > b_cnt) return 1;
	else if (a_cnt == 0) return 0;
	else
	{
		u32_t i, *gasn_arr = gasn_ptr->data, *dz1_asn1_arr = (u32_t *)dz1_asn1_ptr->data;
		u32_t dz1_asn1_uni = 0, gasn_uni = 0;
		for (i = 0; i < a_cnt; i++)
		{
			gasn_uni = gasn_arr[i];
			dz1_asn1_uni = Dz1Endian4_big2host(dz1_asn1_arr[i]);
			if (gasn_uni < dz1_asn1_uni) return -1;
			else if (gasn_uni > dz1_asn1_uni) return 1;
		}
		return 0;
	}
}

static bool_t _unistr_imp_test(Dz1Error *errp)
{
	void *str_ptr = NULL;
	size_t str_byte_sz = 0;
	if ((str_ptr = Dz1String_conv((void *)sample_data, sample_data_len, "ASCII", GASN_LIB_UNIVERSAL_CHARSET, &str_byte_sz)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		UniversalString *v = NULL;
		ASN1WorkSpace ws;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)str_ptr);

		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

		if ((v = (UniversalString *)mpool_calloc(ws.Pmemory, sizeof(UniversalString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
		else if (ASN1_SET_UniversalString(&ws, v, (ASNUINT32 *)str_ptr, (ASNINT32)(str_byte_sz / 4)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrUniversalStr, v, dz1_unistring_ber_enc_gasn, dz1_unistring_dump_gasn, _unistr_cmp, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf(Dz1T("Test Success\n"));
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)str_ptr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _unistr_exp_test(Dz1Error *errp)
{
	Dz1Asn1UniversalStr *v = Dz1Asn1UniversalStr_newFromBuf(sample_data, sample_data_len, "ASCII", errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UniversalStr_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrUniversalStr, v, dz1_unistring_ber_dec_gasn, dz1_unistring_dump_gasn, _unistr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1UniversalStr_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _unistr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x3C, 0x80, 
			0x1C, 0x08, 0x00, 0x00, 0x00, 'A', 0x00, 0x00, 0x00, 'B',											// 8 0x08
			0x1C, 0x20, 
				0x00, 0x00, 0x00, 'a', 0x00, 0x00, 0x00, 'b', 0x00, 0x00, 0x00, 'c', 0x00, 0x00, 0x00, 'd',		// 16 0x10
				0x00, 0x00, 0x00, 'e', 0x00, 0x00, 0x00, 'f', 0x00, 0x00, 0x00, 'g', 0x00, 0x00, 0x00, 'h',		// 16 0x10
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x3C, 0x2C, 
			0x1C, 0x08, 0x00, 0x00, 0x00, 'A', 0x00, 0x00, 0x00, 'B',											// 10	0x0A
			0x1C, 0x20,																							// 2	0x02	12
				0x00, 0x00, 0x00, 'a', 0x00, 0x00, 0x00, 'b', 0x00, 0x00, 0x00, 'c', 0x00, 0x00, 0x00, 'd',		// 16	0x10	28
				0x00, 0x00, 0x00, 'e', 0x00, 0x00, 0x00, 'f', 0x00, 0x00, 0x00, 'g', 0x00, 0x00, 0x00, 'h',		// 16	0x10	44
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrUniversalStr, &ber_def, dz1_unistring_ber_dec_gasn, dz1_unistring_dump_gasn, _unistr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrUniversalStr, &ber_indef, dz1_unistring_ber_dec_gasn, dz1_unistring_dump_gasn, _unistr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _unistr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("UniversalString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_unistr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_unistr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_unistr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// UniversalString Import Test
static void cmd_ber_imp_unistr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_unistr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));

	if (argc != 1) cmd_ber_imp_unistr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_unistr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_unistr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_unistr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_unistr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_unistr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("unistr"));
	if (argc < 2) cmd_ber_imp_unistr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_unistr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_unistr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_unistr_usage(argv[0]);
	}
}
// UniversalString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UniversalString Export Test
static void cmd_ber_exp_unistr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_unistr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("unistr"));
	if (argc != 1) cmd_ber_exp_unistr_usage(n);
	else
	{
		// Command Code Here
	}
}
// UniversalString Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(BMPString, dz1_bmpstring_ber_dec_gasn)
static GASN_ENC_DECLARE(BMPString, dz1_bmpstring_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(BMPString, dz1_bmpstring_dump_gasn, v)

static int _bmpstr_cmp(BMPString *gasn_ptr, Dz1Asn1BMPStr *dz1_asn1_ptr)
{
	u32_t a_cnt = gasn_ptr->nchar, b_cnt = dz1_asn1_ptr->size / 2;
	if (a_cnt < b_cnt) return -1;
	else if (a_cnt > b_cnt) return 1;
	else if (a_cnt == 0) return 0;
	else
	{
		u32_t i;
		u16_t *gasn_arr = gasn_ptr->data, *dz1_asn1_arr = (u16_t *)dz1_asn1_ptr->data;
		u16_t gasn_bmp = 0, dz1_asn1_bmp = 0;
		for (i = 0; i < a_cnt; i++)
		{
			gasn_bmp = gasn_arr[i];
			dz1_asn1_bmp = Dz1Endian2_big2host(dz1_asn1_arr[i]);
			if (gasn_bmp < dz1_asn1_bmp) return -1;
			else if (gasn_bmp > dz1_asn1_bmp) return 1;
		}
		return 0;
	}
}

static bool_t _bmpstr_imp_test(Dz1Error *errp)
{
	void *str_ptr = NULL;
	size_t str_byte_sz = 0;
	if ((str_ptr = Dz1String_conv((void *)sample_data, sample_data_len, "ASCII", GASN_LIB_BMP_CHARSET, &str_byte_sz)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		BMPString *v = NULL;
		ASN1WorkSpace ws;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)str_ptr);

		ASN1_INIT_WS_INFO(&ws);
		pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

		if ((v = (BMPString *)mpool_calloc(ws.Pmemory, sizeof(BMPString), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
		else if (ASN1_SET_BMPString(&ws, v, (ASNUINT16 *)str_ptr, (ASNINT32)(str_byte_sz / 2)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrBMPStr, v, dz1_bmpstring_ber_enc_gasn, dz1_bmpstring_dump_gasn, _bmpstr_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)str_ptr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bmpstr_exp_test(Dz1Error *errp)
{
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bmpstr_cst_test(Dz1Error *errp)
{
	u8_t data_indef[] = 
	{ 
		0x3E, 0x80, 
			0x1E, 0x04, 0x00, 'A', 0x00, 'B',																//  6 0x06
			0x1E, 0x10,																						//  2 0x01	8
				0x00, 'a', 0x00, 'b', 0x00, 'c', 0x00, 'd', 0x00, 'e', 0x00, 'f', 0x00, 'g', 0x00, 'h',		// 16 0x10	24
		0x00, 0x00
	};
	Dz1Binary ber_indef = { data_indef, sizeof(data_indef) };

	u8_t data_def[] = 
	{ 
		0x3E, 0x18, 
			0x1E, 0x04, 0x00, 'A', 0x00, 'B',																//  6 0x06
			0x1E, 0x10,																						//  2 0x01	8
				0x00, 'a', 0x00, 'b', 0x00, 'c', 0x00, 'd', 0x00, 'e', 0x00, 'f', 0x00, 'g', 0x00, 'h',		// 16 0x10	24
	};
	Dz1Binary ber_def = { data_def, sizeof(data_def) };

	if (0) { }
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrBMPStr, &ber_def, dz1_bmpstring_ber_dec_gasn, dz1_bmpstring_dump_gasn, _bmpstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_construct_test(&dz1Asn1TypeDescrBMPStr, &ber_indef, dz1_bmpstring_ber_dec_gasn, dz1_bmpstring_dump_gasn, _bmpstr_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bmpstr_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("BMPString Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_bmpstr_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_bmpstr_exp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_bmpstr_cst_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// BMPString Import Test
static void cmd_ber_imp_bmpstr1_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_bmpstr1(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("primitive"));
	if (argc != 1) cmd_ber_imp_bmpstr1_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_bmpstr2_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <indef | definite>\n"), n); }
static void cmd_ber_imp_bmpstr2(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("construct"));
	if (argc != 2) cmd_ber_imp_bmpstr2_usage(n);
	else
	{
		// Command Code Here
	}
}

static void cmd_ber_imp_bmpstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <primitive | construct>\n"), n); }
static void cmd_ber_imp_bmpstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("bmpstr"));
	if (argc < 2) cmd_ber_imp_bmpstr_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("primitive")) == 0 || Dz1STRCMP(argv[1], Dz1Text("p")) == 0) cmd_ber_imp_bmpstr1(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("construct")) == 0 || Dz1STRCMP(argv[1], Dz1Text("c")) == 0) cmd_ber_imp_bmpstr2(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_bmpstr_usage(argv[0]);
	}
}
// BMPString Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BMPString Export Test
static void cmd_ber_exp_bmpstr_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_bmpstr(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("bmpstr"));
	if (argc != 1) cmd_ber_exp_bmpstr_usage(n);
	else
	{
		// Command Code Here
		Dz1Asn1BMPStr *v = Dz1Asn1BMPStr_newFromBuf(sample_data, sample_data_len, "ASCII", errp);
		if (v == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1BMPStr_delAndSetNull, (void *)&v);
			if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrBMPStr, v, dz1_bmpstring_ber_dec_gasn, dz1_bmpstring_dump_gasn, _bmpstr_cmp, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Thread_printf(Dz1T("Test Success\n"));
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1Asn1BMPStr_delAndSetNull, (void *)&v);
		}
	}
}
// BMPString Export Test
////////////////////////////////////////////////////////////////////////////////
*/
/*
////////////////////////////////////////////////////////////////////////////////
// String Import Test
static void cmd_ber_imp_unicode_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <utf8 | uni | bmp>\n"), n); }
void cmd_ber_imp_unicode(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("unicode"));
	if (argc < 2) cmd_ber_imp_unicode_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("utf8")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("8")) == 0) cmd_ber_imp_utf8str(ptr, argv[0], argc-1, &argv[1]);
 		else if (Dz1STRCMP(argv[1], Dz1Text("uni")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("u")) == 0) cmd_ber_imp_unistr(ptr, argv[0], argc-1, &argv[1]);
 		else if (Dz1STRCMP(argv[1], Dz1Text("bmp")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("b")) == 0) cmd_ber_imp_bmpstr(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_unicode_usage(argv[0]);
	}
}
// String Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// String Export Test
static void cmd_ber_simple_unicode_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <utf8 | uni | bmp | all>\n"), n); }
void cmd_ber_simple_unicode(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("unicode"));
	if (argc != 2) cmd_ber_simple_unicode_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("utf8")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("8")) == 0)	// 12
		{
			if (_utf8str_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("uni")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("u")) == 0)	// 28
		{
			if (_unistr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("bmp")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("b")) == 0)	// 30
		{
			if (_bmpstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_utf8str_test(errp) == FALSE) ERR_OUT(errp);
			else if (_unistr_test(errp) == FALSE) ERR_OUT(errp);
			else if (_bmpstr_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_unicode_usage(argv[0]);
	}
}
// String Export Test
////////////////////////////////////////////////////////////////////////////////

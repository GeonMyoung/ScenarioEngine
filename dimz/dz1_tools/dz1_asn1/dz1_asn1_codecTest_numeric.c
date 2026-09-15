#include "dz1_asn1_codecTest.h"

static GASN_ENC_DECLARE(BOOLEAN, dz1_boolean_ber_enc_gasn)
static GASN_DEC_DECLARE(BOOLEAN, dz1_boolean_ber_dec_gasn)
static GASN_DUMP_SIMPLE_DECLARE(BOOLEAN, dz1_boolean_dump_gasn, v)

static int _boolean_cmp(BOOLEAN *a, Dz1Asn1Bool *b)
{
	if (!*a && *b) return -1;
	else if (*a && !*b) return 1;
	else return 0;
}

static bool_t _bool_imp_test(Dz1Error *errp)
{
	BOOLEAN v1 = TRUE;
	BOOLEAN v2 = FALSE;
	if (0) { }
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrBool, &v1, dz1_boolean_ber_enc_gasn, dz1_boolean_dump_gasn, _boolean_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrBool, &v2, dz1_boolean_ber_enc_gasn, dz1_boolean_dump_gasn, _boolean_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bool_exp_test(Dz1Error *errp)
{
	Dz1Asn1Bool v1 = TRUE, v2 = FALSE;
	if (0) { }
	else if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrBool, &v1, dz1_boolean_ber_dec_gasn, dz1_boolean_dump_gasn, _boolean_cmp, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrBool, &v2, dz1_boolean_ber_dec_gasn, dz1_boolean_dump_gasn, _boolean_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _bool_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("BOOL Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_bool_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_bool_exp_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
/*
////////////////////////////////////////////////////////////////////////////////
// BOOLEAN Import Test
static bool_t _boolean_parse(BOOLEAN *dst, Dz1Str arg, Dz1Error *errp)
{
	Dz1Str temp = NULL;
	if (dst == NULL || Dz1Str_isVoid(arg)) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1Str_dup(arg, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);
		Dz1Str_ucase(temp);
		if (Dz1STRCMP(temp, Dz1T("TRUE")) == 0 || Dz1STRCMP(temp, Dz1T("T")) == 0 || Dz1STRCMP(temp, Dz1T("1")) == 0) (*dst) = 1;
		else if (Dz1STRCMP(temp, Dz1T("FALSE")) == 0 || Dz1STRCMP(temp, Dz1T("F")) == 0 || Dz1STRCMP(temp, Dz1T("0")) == 0) (*dst) = 0;
		else ERR_SET_OUT(errp, EINVAL);
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void cmd_ber_imp_boolean_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <TRUE | FALSE>\n"), n); }
static void cmd_ber_imp_boolean(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("boolean"));
	if (argc != 2) cmd_ber_imp_boolean_usage(n);
	else
	{
		// Command Code Here
	}
}
// BOOLEAN Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BOOLEAN Export Test
static void cmd_ber_exp_boolean_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <TRUE | FALSE>\n"), n); }
static void cmd_ber_exp_boolean(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("boolean"));
	if (argc != 2) cmd_ber_exp_boolean_usage(n);
	else
	{
		// Command Code Here
	}
}
// BOOLEAN Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_ENC_DECLARE(INTEGER, dz1_integer_ber_enc_gasn)
static GASN_DEC_DECLARE(INTEGER, dz1_integer_ber_dec_gasn)
static GASN_DUMP_SIMPLE_DECLARE(INTEGER, dz1_integer_dump_gasn, v)

static s64_t test_value[] =
{
	0x7F,
	0xFF,
	0x100,
	0x1FF,
	-1,
	DZ1INT64(0xFFFFFFFFFFFFFF80),
	DZ1INT64(0xFFFFFFFFFFFFFF00),
	DZ1INT64(0xFFFFFFFFFFFFFE00),
	DZ1INT64(0x8000000000000000)
};
static size_t test_value_cnt = sizeof(test_value) / sizeof(s64_t), i;

static bool_t cmd_ber_imp_integer_all(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	for (i = 0; errp->code == 0 && i < test_value_cnt; i++)
	{
		Dz1Thread_printf(Dz1T("=== Integer Test Entry [%3d] ==================================\n"), i + 1);
		if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrInt, &test_value[i], dz1_integer_ber_enc_gasn, dz1_integer_dump_gasn, _integer_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	if (flag_verbose) Dz1Thread_printf(Dz1T("Done...\n"));
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t cmd_ber_exp_integer_all(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	for (i = 0; errp->code == 0 && i < test_value_cnt; i++)
	{
		Dz1Thread_printf(Dz1T("=== Integer Test Entry [%3d] ==================================\n"), i + 1);
		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrInt, &test_value[i], dz1_integer_ber_dec_gasn, dz1_integer_dump_gasn, _integer_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	if (flag_verbose) Dz1Thread_printf(Dz1T("Done...\n"));
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _integer_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("INTEGER Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (cmd_ber_imp_integer_all(errp) == FALSE) ERR_OUT(errp);
	else if (cmd_ber_exp_integer_all(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// INTEGER Import Test
static void cmd_ber_imp_integer_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <{value} | all>\n"), n); }
static void cmd_ber_imp_integer(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("integer"));
	if (argc != 2) cmd_ber_imp_integer_usage(n);
	else
	{
		// Command Code Here
	}
}
// INTEGER Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// INTEGER Export Test
static void cmd_ber_exp_integer_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <{value} | all>\n"), n); }
static void cmd_ber_exp_integer(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("integer"));
	if (argc != 2) cmd_ber_exp_integer_usage(n);
	else
	{
		// Command Code Here
	}
}
// INTEGER Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_ENC_DECLARE(ENUMERATED, dz1_enumerated_ber_enc_gasn)
static GASN_DEC_DECLARE(ENUMERATED, dz1_enumerated_ber_dec_gasn)
static void dz1_enumerated_dump_gasn(void *ptr, int tab)
{
	ENUMERATED *p = (ENUMERATED *)ptr;
	ASN1_Print_ENUMERATED("v", "", *p);
}

static int _enumerated_cmp(ENUMERATED *a, Dz1Asn1Enum *b)
{
	if (*a < *b) return -1;
	if (*a > *b) return 1;
	return 0;
}

static bool_t cmd_ber_imp_enumerated_all(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	for (i = 0; errp->code == 0 && i < test_value_cnt; i++)
	{
		Dz1Thread_printf(Dz1T("=== Integer Test Entry [%3d] ==================================\n"), i + 1);
		if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrEnum, &test_value[i], dz1_enumerated_ber_enc_gasn, dz1_enumerated_dump_gasn, _enumerated_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	if (flag_verbose) Dz1Thread_printf(Dz1T("Done...\n"));
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t cmd_ber_exp_enumerated_all(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	for (i = 0; errp->code == 0 && i < test_value_cnt; i++)
	{
		Dz1Thread_printf(Dz1T("=== Integer Test Entry [%3d] ==================================\n"), i + 1);
		if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrEnum, &test_value[i], dz1_enumerated_ber_enc_gasn, dz1_enumerated_dump_gasn, _enumerated_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	if (flag_verbose) Dz1Thread_printf(Dz1T("Done...\n"));
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _enum_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("ENUMERATED Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (cmd_ber_imp_enumerated_all(errp) == FALSE) ERR_OUT(errp);
	else if (cmd_ber_exp_enumerated_all(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// ENUMERATED Import Test
static void cmd_ber_imp_enumerated_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <{value} | all>\n"), n); }
static void cmd_ber_imp_enumerated(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("enum"));
	if (argc != 2) cmd_ber_imp_enumerated_usage(n);
	else
	{
		// Command Code Here
	}
}
// ENUMERATED Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ENUMERATED Export Test
static void cmd_ber_exp_enumerated_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <{value} | all>\n"), n); }
static void cmd_ber_exp_enumerated(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("enum"));
	if (argc != 2) cmd_ber_exp_enumerated_usage(n);
	else
	{
		// Command Code Here
	}
}
// ENUMERATED Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_ENC_DECLARE(REAL, dz1_real_ber_enc_gasn)
static GASN_DEC_DECLARE(REAL, dz1_real_ber_dec_gasn)
static GASN_DUMP_SIMPLE_DECLARE(REAL, dz1_real_dump_gasn, v)
static int _real_cmp(REAL *a, Dz1Asn1Real *b)
{
	if (*a < *b) return -1;
	if (*a > *b) return 1;
	return 0;
}

static bool_t _real_imp_test(Dz1Error *errp)
{
	double v = 3.14159265358979323846;
	if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrReal, &v, dz1_real_ber_enc_gasn, dz1_real_dump_gasn, _real_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _real_exp_test(Dz1Error *errp)
{
	double v = 3.14159265358979323846;
	if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrReal, &v, dz1_real_ber_dec_gasn, dz1_real_dump_gasn, _real_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _real_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("REAL Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_real_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_real_exp_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// REAL Import Test
static void cmd_ber_imp_real_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s [<float>]\n"), n); }
static void cmd_ber_imp_real(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("real"));
	if (argc != 1 && argc != 2) cmd_ber_imp_enumerated_usage(n);
	else
	{
		// Command Code Here
	}
}
// REAL Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// REAL Export Test
static void cmd_ber_exp_real_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s [<float>]\n"), n); }
static void cmd_ber_exp_real(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("real"));
	if (argc != 1 && argc != 2) cmd_ber_exp_enumerated_usage(n);
	else
	{
		// Command Code Here
	}
}
// REAL Export Test
////////////////////////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////////////////////////
// NUMERIC Import Test
static void cmd_ber_imp_numeric_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <boolean | integer | enum | real> <params...>\n"), n); }
void cmd_ber_imp_numeric(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("numeric"));
	if (argc < 2) cmd_ber_imp_numeric_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("boolean")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("b")) == 0) cmd_ber_imp_boolean(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("integer")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("i")) == 0) cmd_ber_imp_integer(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("enum")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("e")) == 0) cmd_ber_imp_enumerated(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("real")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("r")) == 0) cmd_ber_imp_real(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_numeric_usage(argv[0]);
	}
}
// NUMERIC Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// NUMERIC Export Test
static void cmd_ber_simple_numeric_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <boolean | integer | enum | real | all>\n"), n); }
void cmd_ber_simple_numeric(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("numeric"));
	if (argc != 2) cmd_ber_simple_numeric_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("boolean")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("b")) == 0)	// 1
		{
			if (_bool_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("integer")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("i")) == 0)	// 2
		{
			if (_integer_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("real")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("r")) == 0)	// 9
		{
			if (_real_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
 		else if (Dz1STRCMP(argv[1], Dz1Text("enum")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("e")) == 0)	// 10
		{
			if (_enum_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_bool_test(errp) == FALSE) ERR_OUT(errp);
			else if (_integer_test(errp) == FALSE) ERR_OUT(errp);
			else if (_enum_test(errp) == FALSE) ERR_OUT(errp);
			else if (_real_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_numeric_usage(argv[0]);
	}
}
// NUMERIC Export Test
////////////////////////////////////////////////////////////////////////////////

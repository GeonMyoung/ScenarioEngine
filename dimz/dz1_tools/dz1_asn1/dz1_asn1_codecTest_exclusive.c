#include "dz1_asn1_codecTest.h"

////////////////////////////////////////////////////////////////////////////////
// NULL Import Test
static Dz1Binary *dz1_null_ber_enc_gasn(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *ret = NULL;

	int status = 0;
	ASN1WorkSpace ws;
	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((status = ASN1_BER_Enc_NULL(&ws, ASN1EXPL)) < 0) { Dz1Thread_printf(Dz1T("err_code = %d\n"), status); ERR_SET_OUT(errp, EFAULT); }
	else if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, Dz1Asn1Codec_ber), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return ret;
}
static void *dz1_null_ber_dec_gasn(Dz1Binary *bin, ASN1WorkSpace *ws, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;
	if (ASN1_BER_Enc_NULL(ws, ASN1EXPL) < 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = mpool_calloc(ws->Pmemory, sizeof(ASNUINT8), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else Dz1Error_set(errp, 0);
	return ret;
}
static void dz1_null_dump_gasn(void *ptr, int tab)
{
	ASNUINT8 *p = (ASNUINT8 *)ptr;
	ASN1_Print_NULL("v", p);
}

static bool_t dz1_null_ber_ingress_test(bool_t verbose, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Binary *bin = NULL;

	if ((bin = dz1_null_ber_enc_gasn(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Asn1Null *v_ptr = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if (verbose)
		{
			Dz1Thread_printf("@@@ BER Stream = ");
			Dz1Binary_dump(bin, 0);
		}

		if ((v_ptr = dz1_asn1_ber_deocde(&dz1Asn1TypeDescrNull, bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Asn1Null_delAndSetNull, (void *)&v_ptr);

			Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1Asn1Null_delAndSetNull, (void *)&v_ptr);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static int _null_cmp(void *gasn_ptr, void *dz1_asn1_ptr)
{
	return 0;
}

static bool_t _null_test(Dz1Error *errp)
{
	Dz1Asn1Null v = Dz1Asn1Null_initializer;
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("NULL Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (dz1_null_ber_ingress_test(flag_verbose, errp) == FALSE) ERR_OUT(errp);
	else if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrNull, &v, dz1_null_ber_dec_gasn, dz1_null_dump_gasn, _null_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
/*
static void cmd_ber_imp_null_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_null(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("null"));
	if (argc != 1) cmd_ber_imp_null_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// NULL Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NULL Export Test
/*
static void cmd_ber_exp_null_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_null(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("null"));
	if (argc != 1) cmd_ber_imp_null_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// NULL Export Test
////////////////////////////////////////////////////////////////////////////////

static u32_t oid_arr[] = { 1, 0, 999, 1, 2, 3, 1, 2 }; 
static u32_t oid_arr_cnt = sizeof(oid_arr) / sizeof(u32_t);

static GASN_ENC_DECLARE(OBJECTIDENTIFIER, dz1_oid_ber_enc_gasn)
static GASN_DEC_DECLARE(OBJECTIDENTIFIER, dz1_oid_ber_dec_gasn)
static GASN_DUMP_SIMPLE_DECLARE(OBJECTIDENTIFIER, dz1_oid_dump_gasn, v)

static bool_t _oid_imp_test(Dz1Error *errp)
{
	OBJECTIDENTIFIER *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (OBJECTIDENTIFIER *)mpool_calloc(ws.Pmemory, sizeof(OBJECTIDENTIFIER), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_OBJECTIDENTIFIER(&ws, v, oid_arr, oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrOID, v, dz1_oid_ber_enc_gasn, dz1_oid_dump_gasn, _oid_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _oid_exp_test(Dz1Error *errp)
{
	Dz1Asn1OID *v = Dz1Asn1OID_new(oid_arr, oid_arr_cnt, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrOID, v, dz1_oid_ber_dec_gasn, dz1_oid_dump_gasn, _oid_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _oid_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("OID Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_oid_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_oid_exp_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// OID Import Test
/*
static void cmd_ber_imp_oid_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_oid(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("oid"));
	if (argc != 1) cmd_ber_imp_oid_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// OID Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// OID Export Test
/*
static void cmd_ber_exp_oid_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_oid(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("oid"));
	if (argc != 1) cmd_ber_exp_oid_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// OID Export Test
////////////////////////////////////////////////////////////////////////////////

static GASN_ENC_DECLARE(RELATIVE_OID, dz1_roid_ber_enc_gasn)
static GASN_DEC_DECLARE(RELATIVE_OID, dz1_roid_ber_dec_gasn)
static GASN_DUMP_SIMPLE_DECLARE(RELATIVE_OID, dz1_roid_dump_gasn, v)
static bool_t _roid_cmp(RELATIVE_OID *a, Dz1Asn1OID *b)
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

static bool_t _roid_imp_test(Dz1Error *errp)
{
	RELATIVE_OID *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (RELATIVE_OID *)mpool_calloc(ws.Pmemory, sizeof(RELATIVE_OID), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_RELATIVE_OID(&ws, v, oid_arr, oid_arr_cnt) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrRelOID, v, dz1_roid_ber_enc_gasn, dz1_roid_dump_gasn, _roid_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _roid_exp_test(Dz1Error *errp)
{
	Dz1Asn1OID *v = Dz1Asn1OID_new(oid_arr, oid_arr_cnt, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1OID_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrRelOID, v, dz1_roid_ber_dec_gasn, dz1_oid_dump_gasn, _oid_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1OID_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static bool_t _roid_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("RELATIVE OID Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_roid_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_roid_exp_test(errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// RelOID Import Test
/*
static void cmd_ber_imp_roid_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_roid(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("reloid"));
	if (argc != 1) cmd_ber_imp_roid_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// RelOID Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// RelOID Export Test
/*
static void cmd_ber_exp_roid_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_exp_roid(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("reloid"));
	if (argc != 1) cmd_ber_exp_oid_usage(n);
	else
	{
		// Command Code Here
	}
}
*/
// RelOID Export Test
////////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////////////////////////
// EXCLUSIVE Import Test
static void cmd_ber_imp_exclusive_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <null | oid | roid> <params...>\n"), n); }
void cmd_ber_imp_exclusive(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("exclusive"));
	if (argc < 2) cmd_ber_imp_exclusive_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("null")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("n")) == 0) cmd_ber_imp_null(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("oid")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("o")) == 0) cmd_ber_imp_oid(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("reloid")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("r")) == 0) cmd_ber_imp_roid(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_exclusive_usage(argv[0]);
	}
}
// EXCLUSIVE Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// EXCLUSIVE Export Test
static void cmd_ber_simple_exclusive_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <null | oid | roid | all>\n"), n); }
void cmd_ber_simple_exclusive(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("exclusive"));
	if (argc != 2) cmd_ber_simple_exclusive_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("null")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("n")) == 0)	// 5
		{
			if (_null_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("oid")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("o")) == 0)	// 6
		{
			if (_oid_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("reloid")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("r")) == 0)	// 13
		{
			if (_roid_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_null_test(errp) == FALSE) ERR_OUT(errp);
			else if (_oid_test(errp) == FALSE) ERR_OUT(errp);
			else if (_roid_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_exclusive_usage(argv[0]);
	}
}
// EXCLUSIVE Export Test
////////////////////////////////////////////////////////////////////////////////

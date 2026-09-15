#include "dz1_asn1_codecTest.h"

static GASN_DEC_DECLARE(UTCTime, dz1_utctime_ber_dec_gasn)
static GASN_ENC_DECLARE(UTCTime, dz1_utctime_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(UTCTime, dz1_utctime_dump_gasn, v)

static int _utctime_cmp(UTCTime*a, Dz1Asn1UTCTime *b)
{
	return _string_cmp(a, b);
}

static bool_t _utctime_imp_test(Dz1Error *errp)
{
	time_t tNow = time(NULL);
	struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;

	ASNINT32 gmt_offset_s = 9 * 60 * 60;
	UTCTime *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (UTCTime *)mpool_calloc(ws.Pmemory, sizeof(UTCTime), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_UTCTime(&ws, v, &tmNow, gmt_offset_s) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrUTCTime, v, dz1_utctime_ber_enc_gasn, dz1_utctime_dump_gasn, _utctime_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Asn1UTCTime *_utctime_gen(bool_t is_local, Dz1Error *errp)
{
	time_t tNow = time(NULL);
	Dz1Asn1UTCTime *ret = NULL;
	if (is_local)
	{
		struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;
		s32_t gmt_offset_min = Dz1Time_GetGmtOffset() / 60;
		if ((ret = Dz1Asn1UTCTime_newFromTM(&tmNow, gmt_offset_min, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if ((ret = Dz1Asn1UTCTime_newFromT(tNow, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

static bool_t _utctime_exp_test(bool_t is_local, Dz1Error *errp)
{
	Dz1Asn1UTCTime *v = _utctime_gen(is_local, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1UTCTime_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrUTCTime, v, dz1_utctime_ber_dec_gasn, dz1_utctime_dump_gasn, _utctime_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1Asn1UTCTime_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _utctime_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("UTCTime Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_utctime_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_utctime_exp_test(TRUE, errp) == FALSE) ERR_OUT(errp);
	else if (_utctime_exp_test(FALSE, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// UTCTime Import Test
static void cmd_ber_imp_utctime_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_utctime(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("utc"));
	if (argc != 1) cmd_ber_imp_utctime_usage(n);
	else
	{
		// Command Code Here
	}
}
// UTCTime Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// UTCTime Export Test
static void cmd_ber_exp_utctime_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <gmt | local>\n"), n); }
static Dz1Asn1UTCTime *_utctime_gen(Dz1Str arg, Dz1Str n, Dz1Error *errp)
{
	Dz1Asn1UTCTime *ret = NULL;
	if (Dz1STRCMP(arg, Dz1T("gmt")) == 0 || Dz1STRCMP(arg, Dz1T("g")) == 0)
	{
		time_t tNow = time(NULL);
		if ((ret = Dz1Asn1UTCTime_newFromT(tNow, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (Dz1STRCMP(arg, Dz1T("local")) == 0 || Dz1STRCMP(arg, Dz1T("l")) == 0)
	{
		time_t tNow = time(NULL);
		struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;
		s32_t gmt_offset_min = Dz1Time_GetGmtOffset() / 60;
		if ((ret = Dz1Asn1UTCTime_newFromTM(&tmNow, gmt_offset_min, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		cmd_ber_exp_utctime_usage(n);
		Dz1Error_set(errp, EINVAL);
	}
	return ret;
}

static void cmd_ber_exp_utctime(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("utc"));
	if (argc != 2) cmd_ber_exp_utctime_usage(n);
	else
	{
		// Command Code Here
	}
}
// UTCTime Export Test
////////////////////////////////////////////////////////////////////////////////
*/

static GASN_DEC_DECLARE(GeneralizedTime, dz1_generaltime_ber_dec_gasn)
static GASN_ENC_DECLARE(GeneralizedTime, dz1_generaltime_ber_enc_gasn)
static GASN_DUMP_SIMPLE_DECLARE(GeneralizedTime, dz1_generaltime_dump_gasn, v)

static int _generaltime_cmp(GeneralizedTime*a, Dz1Asn1GeneralTime *b)
{
	return _string_cmp(a, b);
}

static bool_t _generaltime_imp_test(Dz1Error *errp)
{
	time_t tNow = time(NULL);
	struct tm *tm_p = localtime(&tNow), tmNow = *tm_p;
	ASNINT32 gmt_offset_s = 9 * 60 * 60;

	GeneralizedTime *v = NULL;
	ASN1WorkSpace ws;

	ASN1_INIT_WS_INFO(&ws);
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void *)&ws);

	if ((v = (GeneralizedTime *)mpool_calloc(ws.Pmemory, sizeof(GeneralizedTime), 1)) == NULL) ERR_SET_OUT(errp, ENOMEM);
	else if (ASN1_SET_GeneralizedTime(&ws, v, &tmNow, gmt_offset_s, 333, 3) < 0) ERR_SET_OUT(errp, EFAULT);
	else if (dz1_asn1_ber_ingress_test(&dz1Asn1TypeDescrGeneralTime, v, dz1_generaltime_ber_enc_gasn, dz1_generaltime_dump_gasn, _generaltime_cmp, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	pthread_cleanup_pop(1); // (ASN1_INIT_WS_INFO_cancel, (void *)&ws);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Asn1GeneralTime *_generaltime_gen(bool_t is_local, Dz1Error *errp)
{
	Dz1Asn1GeneralTime *ret = NULL;
	if (is_local)
	{
		Dz1TimeVal64 tvNow = Dz1TimeVal64_get();
		struct tm *tm_p = localtime(&tvNow.tv_sec), tmNow = *tm_p;
		s32_t gmt_offset_min = Dz1Time_GetGmtOffset() / 60;
		if ((ret = Dz1Asn1GeneralTime_newFromTM(&tmNow, tvNow.tv_usec, 6, gmt_offset_min, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		Dz1TimeVal64 tvNow = Dz1TimeVal64_get();
		if ((ret = Dz1Asn1GeneralTime_newFromT(tvNow.tv_sec, tvNow.tv_usec, 6, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

static bool_t _generaltime_exp_test(bool_t is_local, Dz1Error *errp)
{
	Dz1Asn1GeneralTime *v = _generaltime_gen(is_local, errp);
	if (v == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Asn1GeneralTime_delAndSetNull, (void *)&v);

		if (dz1_asn1_ber_egress_test(&dz1Asn1TypeDescrGeneralTime, v, dz1_generaltime_ber_dec_gasn, dz1_generaltime_dump_gasn, _generaltime_cmp, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);


		pthread_cleanup_pop(1); // (Dz1Asn1GeneralTime_delAndSetNull, (void *)&v);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generaltime_test(Dz1Error *errp)
{
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	Dz1Thread_printf(Dz1T("GeneralizedTime Test\n"));
	Dz1Thread_printf(Dz1T("================================================================================\n"));
	if (0) { }
	else if (_generaltime_imp_test(errp) == FALSE) ERR_OUT(errp);
	else if (_generaltime_exp_test(TRUE, errp) == FALSE) ERR_OUT(errp);
	else if (_generaltime_exp_test(FALSE, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////
// GeneralizedTime Import Test
static void cmd_ber_imp_generaltime_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s\n"), n); }
static void cmd_ber_imp_generaltime(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("general"));
	if (argc != 1) cmd_ber_imp_generaltime_usage(n);
	else
	{
		// Command Code Here
	}
}
// GeneralizedTime Import Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GeneralizedTime Export Test
static void cmd_ber_exp_generaltime_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <gmt | local>\n"), n); }
static Dz1Asn1GeneralTime *_generaltime_gen(Dz1Str arg, Dz1Str n, Dz1Error *errp)
{
	Dz1Asn1GeneralTime *ret = NULL;
	if (Dz1STRCMP(arg, Dz1T("gmt")) == 0 || Dz1STRCMP(arg, Dz1T("g")) == 0)
	{
		Dz1TimeVal64 tvNow = Dz1TimeVal64_get();
		if ((ret = Dz1Asn1GeneralTime_newFromT(tvNow.tv_sec, tvNow.tv_usec, 6, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (Dz1STRCMP(arg, Dz1T("local")) == 0 || Dz1STRCMP(arg, Dz1T("l")) == 0)
	{
		Dz1TimeVal64 tvNow = Dz1TimeVal64_get();
		struct tm *tm_p = localtime(&tvNow.tv_sec), tmNow = *tm_p;
		s32_t gmt_offset_min = Dz1Time_GetGmtOffset() / 60;
		if ((ret = Dz1Asn1GeneralTime_newFromTM(&tmNow, tvNow.tv_usec, 6, gmt_offset_min, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		cmd_ber_exp_utctime_usage(n);
		Dz1Error_set(errp, EINVAL);
	}
	return ret;
}
static void cmd_ber_exp_generaltime(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("general"));
	if (argc != 2) cmd_ber_exp_generaltime_usage(n);
	else
	{
	}
}
// GeneralizedTime Export Test
////////////////////////////////////////////////////////////////////////////////
*/

/*
////////////////////////////////////////////////////////////////////////////////
// Time Import Test
static void cmd_ber_imp_time_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <utc | general>\n"), n); }
void cmd_ber_imp_time(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("time"));
	if (argc < 2) cmd_ber_imp_time_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("utc")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("u")) == 0) cmd_ber_imp_utctime(ptr, argv[0], argc-1, &argv[1]);
		else if (Dz1STRCMP(argv[1], Dz1Text("general")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("g")) == 0) cmd_ber_imp_generaltime(ptr, argv[0], argc-1, &argv[1]);
		else cmd_ber_imp_time_usage(argv[0]);
	}
}
// String Import Test
////////////////////////////////////////////////////////////////////////////////
*/

////////////////////////////////////////////////////////////////////////////////
// Time Export Test
static void cmd_ber_simple_time_usage(Dz1Str n) { Dz1Thread_printf(Dz1Text("Usage] %s <utc | general | all>\n"), n); }
void cmd_ber_simple_time(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[])
{
	TCHAR n[64];
	DZ1_ERROR_SAFE_VAR(errp, err);
	//TestEnv *env = (TestEnv *)ptr;
	Dz1STRCPY(n, parent_cmd); Dz1STRCAT(n, Dz1Text(" ")); Dz1STRCAT(n, Dz1Text("time"));
	if (argc != 2) cmd_ber_simple_time_usage(n);
	else
	{
		if (0) { }
		else if (Dz1STRCMP(argv[1], Dz1Text("utc")) == 0		|| Dz1STRCMP(argv[1], Dz1Text("u")) == 0)	// 23
		{
			if (_utctime_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("general")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("g")) == 0)	// 24
		{
			if (_generaltime_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (Dz1STRCMP(argv[1], Dz1Text("all")) == 0	|| Dz1STRCMP(argv[1], Dz1Text("a")) == 0)
		{
			if (0) { }
			else if (_utctime_test(errp) == FALSE) ERR_OUT(errp);
			else if (_generaltime_test(errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else cmd_ber_simple_time_usage(argv[0]);
	}
}
// Time Export Test
////////////////////////////////////////////////////////////////////////////////

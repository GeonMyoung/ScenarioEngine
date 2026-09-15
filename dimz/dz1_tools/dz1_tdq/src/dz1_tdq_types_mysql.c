#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_usleep.h>

#include "dz1_tdq_types.h"
#include "dz1_tdq_var_def_util.h"

#if DBH_ENGINE == DBH_ENGINE_MY_SQL

///////////////////////////////////////////////////////////////////////////////
// DB Interface Argument
Dz1TdqDbConnArg *Dz1TdqDbConnArg_new(Dz1Str drv_name, Dz1Str svr_addr, u16_t svr_port, Dz1Str user, Dz1Str pw, Dz1Str dbn_opt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbConnArg *ret = (Dz1TdqDbConnArg *)Dz1Calloc(sizeof(Dz1TdqDbConnArg), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqDbConnArg_delAndSetNull, (void *)&ret);
		if (Dz1Str_isVoid(drv_name) == FALSE && (ret->drv_name = Dz1Str_clone(drv_name, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(svr_addr) == FALSE && (ret->svr_addr = Dz1Str_clone(svr_addr, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(user) == FALSE && (ret->user = Dz1Str_clone(user, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(pw) == FALSE && (ret->pw = Dz1Str_clone(pw, errp)) == NULL) ERR_OUT(errp);
		else if (Dz1Str_isVoid(dbn_opt) == FALSE && (ret->dbn_opt = Dz1Str_clone(dbn_opt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->svr_port = svr_port;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqDbConnArg_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1TdqDbConnArg *Dz1TdqDbConnArg_clone(Dz1TdqDbConnArg *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbConnArg *ret = Dz1TdqDbConnArg_new(src->drv_name, src->svr_addr, src->svr_port, src->user, src->pw, src->dbn_opt, errp);
	if (ret == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1TdqDbConnArg_del(Dz1TdqDbConnArg *p)
{
	if (p != NULL)
	{
		Dz1Str_delAndSetNull(&p->drv_name);
		Dz1Str_delAndSetNull(&p->svr_addr);
		Dz1Str_delAndSetNull(&p->user);
		Dz1Str_delAndSetNull(&p->pw);
		Dz1Str_delAndSetNull(&p->dbn_opt);
		Dz1Free(p);
	}
}

void Dz1TdqDbConnArg_dump(Dz1TdqDbConnArg *p, int tab)
{
	Dz1ElasticBuf *elb = NULL;
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else if ((elb = Dz1ElasticBuf_new(64, FALSE, NULL)) == NULL) Dz1Thread_printf(Dz1T("#error\n"));
	else
	{
		Dz1Str str = NULL;
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&elb);
		if (0) { }
		else if (Dz1ElasticBuf_pushStr(elb, Dz1Str_isVoid(p->user) ? Dz1Text("NULL") : p->user, NULL) == FALSE) Dz1Thread_printf(Dz1T("#error\n"));
		else if (Dz1ElasticBuf_pushChr(elb, Dz1Text('@'), NULL) == FALSE) Dz1Thread_printf(Dz1T("#error\n"));
		else if (Dz1ElasticBuf_pushStr(elb, Dz1Str_isVoid(p->svr_addr) ? Dz1Text("NULL") : p->svr_addr, NULL) == FALSE) Dz1Thread_printf(Dz1T("#error\n"));
		else if (Dz1ElasticBuf_pushChr(elb, Dz1Text('('), NULL) == FALSE) Dz1Thread_printf(Dz1T("#error"));
		else if (Dz1ElasticBuf_pushStr(elb, Dz1Str_isVoid(p->dbn_opt) ? Dz1Text("NULL") : p->dbn_opt, NULL) == FALSE) Dz1Thread_printf(Dz1T("#error\n"));
		else if (Dz1ElasticBuf_pushChr(elb, Dz1Text(')'), NULL) == FALSE) Dz1Thread_printf(Dz1T("#error\n"));
		else if ((str = Dz1ElasticBuf_flattenStr(elb, NULL)) == NULL) Dz1Thread_printf(Dz1T("#error\n"));
		else Dz1Str_dump(str, tab);
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&elb);
	}
}
// DB Interface Argument
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Misc Utility
void sql_error_print(HSTMT h_query)
{
	SQLINTEGER sql_error = 0;
	SQLSMALLINT ret_len = 0;
	SQLTCHAR sql_state[16] = { 0, }, sql_err_msg[1024] = { 0, };
	SQLGetDiagRec(SQL_HANDLE_STMT, h_query, 1, sql_state, &sql_error, sql_err_msg, 1024, &ret_len);
	Dz1Thread_printf(Dz1T("!!! DB Access Fail State = %s\n"), sql_state); // Dz1Str_dump(sql_state, 0);
	Dz1Thread_printf(Dz1T("!!! DB Access Fail Message = %s\n"), sql_err_msg); // Dz1Str_dump(sql_err_msg, 0);
}
// Misc Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// dbh API
static void _sql_alloc_env_cancel(void *pp_h_db_env)
{
	HENV *p = (HENV *)pp_h_db_env;
	if ((*p) != SQL_NULL_HENV) SQLFreeEnv(*p);
	*p = NULL;
}

static bool_t dbh_connect(Dz1TdqDbIface *dbe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbConnArg *arg = dbe->arg;
	if(SQL_ERROR == SQLAllocEnv(&dbe->h_db_env)) ERR_SET_OUT(errp, EFAULT);
	else
	{
		pthread_cleanup_push(_sql_alloc_env_cancel, (void *)&dbe->h_db_env);
		if(SQL_ERROR == SQLAllocConnect(dbe->h_db_env, &dbe->h_odbc)) ERR_SET_OUT(errp, EFAULT);
		else
		{
			RETCODE status;
			s16_t short_result = 0;
			TCHAR conn_out_str[1025] = { 0, };
			TCHAR conn_in_str[1025] = { 0, };
			if (Dz1Str_isVoid(arg->dbn_opt) == FALSE)
				Dz1SNPRINTF(conn_in_str, 1024, Dz1Text("DRIVER={%s};SERVER=%s;PORT=%u;USER=%s;PASSWORD=%s;DATABASE=%s;OPTION=3;"),
														arg->drv_name, arg->svr_addr, arg->svr_port, arg->user, arg->pw, arg->dbn_opt);
			else
				Dz1SNPRINTF(conn_in_str, 1024, Dz1Text("DRIVER={%s};SERVER=%s;PORT=%u;USER=%s;PASSWORD=%s;OPTION=3;"),
														arg->drv_name, arg->svr_addr, arg->svr_port, arg->user, arg->pw);

			status = SQLDriverConnect(dbe->h_odbc, NULL, (SQLTCHAR *)conn_in_str, (SQLSMALLINT)(Dz1STRLEN(conn_in_str)),
									  conn_out_str, (SQLSMALLINT)(sizeof(TCHAR) * 1024), &short_result, SQL_DRIVER_NOPROMPT);
			if (status != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO)
			{
				SQLINTEGER sql_error = 0;
				SQLSMALLINT ret_len = 0;
				SQLTCHAR sql_state[16] = { 0, }, sql_err_msg[1024] = { 0, };
				SQLGetDiagRec(SQL_HANDLE_DBC, dbe->h_odbc, 1, sql_state, &sql_error, sql_err_msg, 1024, &ret_len);
				Dz1Thread_printf(Dz1T("!!! DB Access Fail State = %s\n"), sql_state); // Dz1Str_dump(sql_state, 0);
				Dz1Thread_printf(Dz1T("!!! DB Access Fail Message = %s\n"), sql_err_msg); // Dz1Str_dump(sql_err_msg, 0);
				ERR_SET_OUT(errp, EFAULT);
			}
			else
			{
				SQLSetConnectAttr(dbe->h_odbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF, SQL_IS_UINTEGER);
				Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (_sql_alloc_env_cancel, (void *)&dst->h_db_env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static void dbh_disconnect(Dz1TdqDbIface *p)
{
	if (p->h_odbc != SQL_NULL_HDBC)
		SQLFreeConnect(p->h_odbc);
	p->h_odbc = NULL;

	if (p->h_db_env != SQL_NULL_HENV)
		SQLFreeEnv(p->h_db_env);
	p->h_db_env = NULL;
}

static bool_t dbe_reconnect(Dz1TdqDbIface *dbe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dbe == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dbh_disconnect(dbe);
		Dz1Thread_usleep(10000);

		if (dbh_connect(dbe, errp) == FALSE) ERR_OUT(errp);
		else 
		{
			Dz1Thread_usleep(10000);
			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// dbh API
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DB Interface Basic
Dz1TdqDbIface *Dz1TdqDbIface_new(Dz1TdqDbConnArg *arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqDbIface *ret = NULL;
	
	if ((ret = (Dz1TdqDbIface *)Dz1Calloc(sizeof(Dz1TdqDbIface), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqDbIface_delAndSetNull, (void *)&ret);
		ret->arg = arg;
		if (dbh_connect(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqDbIface_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqDbIface_del(Dz1TdqDbIface *p)
{
	if (p == NULL) return;
	dbh_disconnect(p);
	Dz1Free(p);
}

bool_t Dz1TdqDbIface_reconn(Dz1TdqDbIface *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dbe_reconnect(p, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ERR_IS_SUCCESS(errp);
}
// DB Interface Basic
///////////////////////////////////////////////////////////////////////////////

static bool_t _dbe_allocSqlStmt(Dz1TdqDbIface *dbe, HSTMT *ret_h, Dz1Error *errp)
{
	SQLRETURN status;
	if ((status = SQLAllocStmt(dbe->h_odbc, ret_h)) != SQL_SUCCESS)
	{
		if (status == SQL_INVALID_HANDLE) ERR_SET_OUT(errp, EINVAL);
		else
		{
			SQLINTEGER sql_error = 0;
			SQLSMALLINT ret_len = 0;
			SQLTCHAR sql_state[16] = { 0, }, sql_err_msg[1024] = { 0, };
			SQLGetDiagRec(SQL_HANDLE_DBC, dbe->h_odbc, 1, sql_state, &sql_error, sql_err_msg, 1024, &ret_len);

			if (0) { }
			else if (Dz1STRCMP(sql_state, Dz1Text("08003")) == 0) Dz1Error_set(errp, EPIPE);
			else if (Dz1STRCMP(sql_state, Dz1Text("S0002")) == 0) Dz1Error_set(errp, ENOSYS);
			else
			{
				Dz1Thread_printf(Dz1T("!!! DB Access Fail State = %s\n"), sql_state); // Dz1Str_dump(sql_state, 0);
				Dz1Thread_printf(Dz1T("!!! DB Access Fail Message = %s\n"), sql_err_msg); // Dz1Str_dump(sql_err_msg, 0);
				ERR_SET_OUT(errp, EFAULT);
			}
		}
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t dbe_allocSqlStmt(Dz1TdqDbIface *dbe, HSTMT *ret_h, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (_dbe_allocSqlStmt(dbe, ret_h, errp) == FALSE)
	{
		if (errp->code != EPIPE) ERR_OUT(errp);
		// EPIPE
		else 
		{
			Dz1Thread_printf(Dz1T("### DB Session Expired -> Reconnect\n"));
			if (dbe_reconnect(dbe, errp) == FALSE) ERR_OUT(errp);
			else if (_dbe_allocSqlStmt(dbe, ret_h, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct MstmtBindData
{
	Dz1TdqSqlVarPresent			present;
	int							c_type;
	int							q_type;
	size_t						size;
} MstmtBindData;

static MstmtBindData *MstmtBindData_find(MstmtBindData *tbl, Dz1TdqSqlVarPresent v)
{
	MstmtBindData *i;
	for (i = tbl; i->present != Dz1TdqSqlVarPresent_max; i++)
		if (i->present == v) return i;
	return NULL;
}

static MstmtBindData mstmtBindData[] =
{
	{ Dz1TdqSqlVarPresent_s8,			SQL_C_TINYINT,	SQL_TINYINT,		sizeof(u8_t) },
	{ Dz1TdqSqlVarPresent_u8,			SQL_C_UTINYINT, SQL_TINYINT,		sizeof(u8_t) },
	{ Dz1TdqSqlVarPresent_s16,			SQL_C_SSHORT,	SQL_SMALLINT,		sizeof(u16_t) },
	{ Dz1TdqSqlVarPresent_u16,			SQL_C_USHORT,	SQL_SMALLINT,		sizeof(u16_t) },
	{ Dz1TdqSqlVarPresent_s32,			SQL_C_SLONG,	SQL_INTEGER,		sizeof(u32_t) },
	{ Dz1TdqSqlVarPresent_u32,			SQL_C_ULONG,	SQL_INTEGER,		sizeof(u32_t) },
	{ Dz1TdqSqlVarPresent_s64,			SQL_C_SBIGINT,	SQL_BIGINT,			sizeof(u64_t) },
	{ Dz1TdqSqlVarPresent_u64,			SQL_C_UBIGINT,	SQL_BIGINT,			sizeof(u64_t) },
	{ Dz1TdqSqlVarPresent_r32,			SQL_C_FLOAT,	SQL_FLOAT,			sizeof(float) },
	{ Dz1TdqSqlVarPresent_r64,			SQL_C_DOUBLE,	SQL_DOUBLE,			sizeof(double) },

	{ Dz1TdqSqlVarPresent_string,		SQL_C_TCHAR,	SQL_CHAR,			0 },
	{ Dz1TdqSqlVarPresent_vstring,		SQL_C_TCHAR,	SQL_VARCHAR,		0 },
	{ Dz1TdqSqlVarPresent_tstring,		SQL_C_TCHAR,	SQL_WCHAR,			0 },
	{ Dz1TdqSqlVarPresent_vtstring,		SQL_C_TCHAR,	SQL_WVARCHAR,		0 },
	{ Dz1TdqSqlVarPresent_binary,		SQL_C_BINARY,	SQL_BINARY,			0 },
	{ Dz1TdqSqlVarPresent_vbinary,		SQL_C_BINARY,	SQL_VARBINARY,		0 },
	
	{ Dz1TdqSqlVarPresent_ymd,			SQL_C_DATE,		SQL_DATE,			0 },
	{ Dz1TdqSqlVarPresent_hms,			SQL_C_TIME,		SQL_TIME,			0 },
	{ Dz1TdqSqlVarPresent_stamp,		SQL_C_TIMESTAMP,SQL_TIMESTAMP,		0 },
	
	{ Dz1TdqSqlVarPresent_blob,			SQL_C_BINARY,	SQL_LONGVARBINARY,	0 },
	{ Dz1TdqSqlVarPresent_blobL,		SQL_C_BINARY,	SQL_LONGVARBINARY,	0 },
	{ Dz1TdqSqlVarPresent_max }
};

///////////////////////////////////////////////////////////////////////////////
// Query Argument Bind
static SQLLEN sql_param_null_ind = SQL_NULL_DATA;
static SQLLEN sql_param_str_nts = SQL_NTS;
static SQLLEN sql_data_at_exec = SQL_DATA_AT_EXEC;

static bool_t HSTMT_paramBind(HSTMT h_query, int param_idx, Dz1TdqSqlVar *var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MstmtBindData *api = NULL;
	if (h_query == NULL || var == NULL || param_idx == 0) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if (var->present == Dz1TdqSqlVarPresent_nul)
	{	// Null 을 Bind 하는 경우 size 는 Null Indicator 로
		sql_param_null_ind = SQL_NULL_DATA;
		if ((api = MstmtBindData_find(mstmtBindData, var->x.nul)) == NULL) 
			ERR_SET_OUT(errp, ENOSYS);
		else if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, NULL, 0, &sql_param_null_ind))
		{
			sql_error_print(h_query);
			ERR_SET_OUT(errp, EFAULT);
		}
		else Dz1Error_set(errp, 0);
	}
	else if ((api = MstmtBindData_find(mstmtBindData, var->present)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		u8_t category = (u8_t)(var->present & 0xF0);
		switch(category)
		{
		case 0x00:	// Number
		case 0x10:	// Real
			if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, var->x.b1, api->size, NULL))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		case 0x20:	// String & Binary
			if ( ((var->present & 0xE)>>1) == 0x2)
			{	// Binary 인 경우, Buffer 에 있는 Length 를 size 로
				Dz1Binary *bin = var->x.binary;	// Dz1Binary is same as Dz1TdqSqlStr
				SQLLEN bin_size = (SQLLEN)bin->size;
				if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, bin->data, bin->size, &bin_size))
				{
					sql_error_print(h_query);
					ERR_SET_OUT(errp, EFAULT);
				}
				else Dz1Error_set(errp, 0);
			}
			else
			{	// String 인 경우,size 를 NTS로
				Dz1TdqSqlStr *str = var->x.string;
				if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, str->text, 0, &sql_param_str_nts))
				{
					sql_error_print(h_query);
					ERR_SET_OUT(errp, EFAULT);
				}
				else Dz1Error_set(errp, 0);
			}
			break;
		case 0x30:	// Date & Time 인경우 size 무쓸모
			if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, var->x.__ptr__, 0, NULL))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		case 0x40:	// Blob 인 경우 size 를 SQL_DATA_AT_EXEC로
			if (SQL_SUCCESS != SQLBindParameter(h_query, param_idx, SQL_PARAM_INPUT, api->c_type, api->q_type, 0, 0, (SQLPOINTER)DZ1_VAL2PTR32(param_idx), 0, &sql_data_at_exec))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t HSTMT_paramArrayBind(HSTMT h_query, Dz1TdqSqlVar *arg_arr[], u32_t arg_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (arg_arr == NULL || arg_cnt == 0) Dz1Error_set(errp, 0);
	else
	{
		u32_t i;
		for (i = 0; errp->code == 0 && i < arg_cnt; i++)
		{
			if (HSTMT_paramBind(h_query, (int)i + 1, arg_arr[i], errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Query Argument Bind
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Select Column Bind
static bool_t HSTMT_columnBind(HSTMT h_query, int col_idx, Dz1TdqSqlVar *var, SQLLEN *ret_status, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	MstmtBindData *api = NULL;
	if (h_query == NULL || var == NULL || col_idx == 0)
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((api = MstmtBindData_find(mstmtBindData, var->present)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else
	{
		SQLLEN *temp_len = NULL;
		u8_t category = (u8_t)(var->present & 0xF0);
		switch(category)
		{
		case 0x00:	// Number
		case 0x10:	// Real
			if (SQL_SUCCESS != SQLBindCol(h_query, col_idx, api->c_type, var->x.b1, api->size, ret_status))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		case 0x20:	// String & Binary
			if ( ((var->present & 0xE)>>1) == 0x2)
			{	// Binary 인 경우 Buffer 에 할당된 크기로
				Dz1Binary *bin = var->x.binary;
				if (SQL_SUCCESS != SQLBindCol(h_query, col_idx, api->c_type, bin->data, bin->size, ret_status))
				{
					sql_error_print(h_query);
					ERR_SET_OUT(errp, EFAULT);
				}
				else Dz1Error_set(errp, 0);
			}
			else
			{	// String 인 경우 Buffer 에 할당된 크기로
				Dz1TdqSqlStr *str = var->x.string;
				if (SQL_SUCCESS != SQLBindCol(h_query, col_idx, api->c_type, str->text, str->alloc_byte - sizeof(TCHAR), ret_status))
				{
					sql_error_print(h_query);
					ERR_SET_OUT(errp, EFAULT);
				}
				else Dz1Error_set(errp, 0);
			}
			break;
		case 0x30:	// Date & Time 인 경우 0
			if (SQL_SUCCESS != SQLBindCol(h_query, col_idx, api->c_type, var->x.__ptr__, 0, ret_status))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		case 0x40:	// BLOB인 경우 SQL_DATA_AT_EXEC로
			if (SQL_SUCCESS != SQLBindCol(h_query, col_idx, api->c_type, (SQLPOINTER)-1, 0, ret_status))
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t HSTMT_columnArrayBind(HSTMT h_query, Dz1TdqSqlVar *col_arr[], SQLLEN col_stat[], u32_t col_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (h_query == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (col_arr == NULL || col_stat == NULL || col_cnt == 0) Dz1Error_set(errp, 0);
	else
	{
		u32_t i;
		for (i = 0; errp->code == 0 && i < col_cnt; i++)
		{
			if (HSTMT_columnBind(h_query, i + 1, col_arr[i], &col_stat[i], errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}

	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Select Column Bind
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Command
static __inline__ void _sql_alloc_stmt_cancel(void *ptr)
{
	HSTMT h_query = (HSTMT)ptr;
	SQLFreeStmt(h_query, SQL_DROP);
}

static RETCODE sqlCmd_dataSupply_bin(HSTMT h_query, Dz1Binary *bin)
{
	RETCODE chk;
	chk = SQLPutData(h_query, bin->data, bin->size);
	chk = SQLPutData(h_query, bin->data, 0);
	return chk;
}

static RETCODE sqlCmd_dataSupply_ref(HSTMT h_query, Dz1TdqSqlBlobRef *refb)
{
	RETCODE chk;
	chk = SQLPutData(h_query, refb->ptr, refb->sz);
	chk = SQLPutData(h_query, refb->ptr, 0);
	return chk;
}

static RETCODE sqlCmd_dataSupply_file(HSTMT h_query, Dz1Str fn, Dz1Error *errp)
{
	RETCODE chk;
	FILE *fp = Dz1FileStream_open(fn, Dz1Text("rb"), errp);
	if (fp == NULL) ERR_SET_OUT(errp, errno);
	else
	{
		u8_t buf[4096];
		size_t sz = 0;
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		while((sz = fread(buf, sizeof(u8_t), 4986, fp)) > 0)
			chk = SQLPutData(h_query, buf, sz);
		chk = SQLPutData(h_query, buf, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return chk;
}

static RETCODE sqlCmd_dataSupply(HSTMT h_query, Dz1TdqSqlVar **arg_arr, u32_t arg_cnt, Dz1Error *errp)
{
	RETCODE st = 0;

	u32_t idx = 0;
	SQLPOINTER sql_ptr = NULL;
	Dz1TdqSqlVar *target = NULL;

	while(errp->code == 0 && (st = SQLParamData(h_query, &sql_ptr)) == SQL_NEED_DATA)
	{
		idx = ((u32_t)DZ1_PTR2VAL32(sql_ptr) - 1);
		target = arg_arr[idx];
		if (((u8_t)(target->present & 0xF0)) != 0x40) ERR_SET_OUT(errp, EFAULT);
		else
		{
			RETCODE chk = 0;
			Dz1TdqSqlBlob *blob = target->x.blob;
			Dz1TdqSqlBlobToDB *ctx = blob->writeToDB;
			Dz1Binary *bin = NULL;
			Dz1TdqSqlBlobRef *refb = NULL;
			switch(ctx->present)
			{
			case Dz1TdqSqlBlobToDBPresent_embedded:
				sqlCmd_dataSupply_bin(h_query, ctx->x.embedded);
				break;
			case Dz1TdqSqlBlobToDBPresent_ref_buf:
				sqlCmd_dataSupply_ref(h_query, ctx->x.ref_buf);
				break;
			case Dz1TdqSqlBlobToDBPresent_saved_file:
				sqlCmd_dataSupply_file(h_query, ctx->x.saved_file, errp);
				break;
			default:
				break;
			}
		}
	}
	return st;
}

typedef struct MySqlStatus
{
	SQLINTEGER	 sql_error;
	SQLTCHAR	 sql_state[8];
	SQLTCHAR	 sql_err_msg[256];
	SQLSMALLINT	 sql_err_msg_len;
} MySqlStatus;

static void MySqlStatus_dump(MySqlStatus *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("[err:%d][S:%s]\n"), p->sql_error, p->sql_state);
		Dz1Thread_tprintf(tab, Dz1T("%s\n"), p->sql_err_msg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}

#define MySqlStatus_init		{ 0, { 0, }, { 0, }, 0 }
static bool_t _sqlGetQueryState(HSTMT h_query, MySqlStatus *dst)
{
	bool_t ret = FALSE;
	if (h_query != NULL && dst != NULL)
	{
		SQLSMALLINT status = SQLGetDiagRec(SQL_HANDLE_STMT, h_query, 1, dst->sql_state, &dst->sql_error, dst->sql_err_msg, 255, &dst->sql_err_msg_len);
		if (status == SQL_SUCCESS || status == SQL_SUCCESS_WITH_INFO) ret = TRUE;
	}
	return ret;
}

static void _sqlTranslateQueryState(Dz1Error *dst, MySqlStatus *src, Dz1Str query, Dz1TdqSqlVar **arg_arr, u32_t arg_cnt, char *__file__, int __line__)
{
	if (dst != NULL && src != NULL)
	{
		if (Dz1STRCMP(src->sql_state, Dz1Text("S0002")) == 0) _Dz1Error_set(dst, ENOSYS, __file__, __line__);
		else
		{
			u32_t i;
			switch(src->sql_error)
			{
			case 1022: _Dz1Error_set(dst, EEXIST, __file__, __line__); break;
			case 1037: _Dz1Error_set(dst, ENOMEM, __file__, __line__); break;
			case 1038: _Dz1Error_set(dst, ENOMEM, __file__, __line__); break;
			default:
				_Dz1Error_set(dst, EFAULT, __file__, __line__);
				Dz1Thread_printf(Dz1T("!!! ERROR = ")); MySqlStatus_dump(src, 0); 
				Dz1Thread_printf(Dz1T("!!! Query = ")); Dz1Str_dump(query, 0);
				for (i = 0; i < arg_cnt; i++)
				{
					Dz1Thread_printf(Dz1T("ARG[%03X] = "), i); 
					Dz1TdqSqlVar_dump(arg_arr[i], 0);
				}
				break;
			}
		}
	}
}
#define sqlTranslateQueryState(er_p, st_p, qry, ar_arr, ar_cnt)		_sqlTranslateQueryState((er_p), (st_p), (qry), (ar_arr), (ar_cnt), __FILE__, __LINE__)

static bool_t _sqlCmdExecute(HSTMT h_query, Dz1Str query, Dz1TdqSqlVar **arg_arr, u32_t arg_cnt, Dz1Error *errp)
{
	RETCODE status = 0;
	if ((status = SQLExecDirect(h_query, (SQLTCHAR *)query, SQL_NTS)) != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) 
	{	// error occur
		if (status == SQL_NEED_DATA)
		{	// Need More Data
			RETCODE st = sqlCmd_dataSupply(h_query, arg_arr, arg_cnt, errp);
			if (st != SQL_SUCCESS && st != SQL_SUCCESS_WITH_INFO)
			{
				Dz1Thread_printf(Dz1T("status = %d\n"), status);
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
		}
		else
		{	// Critical Error
			SQLINTEGER sql_error = 0;
			SQLSMALLINT ret_len = 0;
			SQLTCHAR sql_state[16] = { 0, }, sql_err_msg[1024] = { 0, };
			SQLGetDiagRec(SQL_HANDLE_STMT, h_query, 1, sql_state, &sql_error, sql_err_msg, 1024, &ret_len);

			if (Dz1STRCMP(sql_state, Dz1Text("S0002")) == 0) Dz1Error_set(errp, ENOSYS);
			else
			{
				u32_t i;
				Dz1Thread_printf(Dz1T("!!! DB Access Fail State = %s\n"), sql_state); // Dz1Str_dump(sql_state, 0);
				Dz1Thread_printf(Dz1T("!!! DB Access Fail Message = %s\n"), sql_err_msg); // Dz1Str_dump(sql_err_msg, 0);
				Dz1Thread_printf(Dz1T("!!! Query = %s\n"), query); // Dz1Str_dump(query, 0);
				for (i = 0; i < arg_cnt; i++)
				{
					Dz1Thread_printf(Dz1T("ARG[%03X] = "), i); 
					Dz1TdqSqlVar_dump(arg_arr[i], 0);
				}
				ERR_SET_OUT(errp, EFAULT);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

/*
static bool_t _sqlCmd(HSTMT h_query, Dz1Str query, Dz1TdqSqlVar **arg_arr, u32_t arg_cnt, Dz1Error *errp)
{
	RETCODE status = 0;

	if (HSTMT_paramArrayBind(h_query, arg_arr, arg_cnt, errp) == FALSE) ERR_OUT(errp);
	else if ((status = SQLExecDirect(h_query, (SQLTCHAR *)query, SQL_NTS)) != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) 
	{
		if (status == SQL_NEED_DATA)
		{	// Need More Data
			RETCODE st = sqlCmd_dataSupply(h_query, arg_arr, arg_cnt, errp);
			if (st != SQL_SUCCESS && st != SQL_SUCCESS_WITH_INFO)
			{
				Dz1Thread_printf("status = %d\n", status);
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
			}
		}
		else
		{	// Critical Error
			SQLINTEGER sql_error = 0;
			SQLSMALLINT ret_len = 0;
			SQLTCHAR sql_state[16] = { 0, }, sql_err_msg[1024] = { 0, };
			SQLGetDiagRec(SQL_HANDLE_STMT, h_query, 1, sql_state, &sql_error, sql_err_msg, 1024, &ret_len);

			if (Dz1STRCMP(sql_state, Dz1Text("S0002")) == 0) Dz1Error_set(errp, ENOSYS);
			else
			{
				Dz1Thread_printf("!!! DB Access Fail State = "); Dz1Str_dump(sql_state, 0);
				Dz1Thread_printf("!!! DB Access Fail Message = "); Dz1Str_dump(sql_err_msg, 0);
				ERR_SET_OUT(errp, EFAULT);
			}
		}
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
*/

bool_t Dz1TdqDbIface_sqlCmd_(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqSqlVar **arr, u32_t cnt, bool_t commit, Dz1Error *errp)
{
	HSTMT h_query;
	if (dbe == NULL || dbe->h_odbc == NULL) ERR_SET_OUT(errp, EPIPE);
	else if (dbe_allocSqlStmt(dbe, &h_query, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
	else
	{
		RETCODE status = 0;
		pthread_cleanup_push(_sql_alloc_stmt_cancel, (void *)h_query);

		if (HSTMT_paramArrayBind(h_query, arr, cnt, errp) == FALSE) ERR_OUT(errp);
		else if (_sqlCmdExecute(h_query, query, arr, cnt, errp) == FALSE) 
		{
			Dz1Thread_printf(Dz1T("Failed Query = %s\n"), query);
			ERR_OUT(errp);
		}
		else 
		{
			if (commit) SQLEndTran(SQL_HANDLE_DBC, dbe->h_odbc, SQL_COMMIT);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (_sql_alloc_stmt_cancel, (void *)h_query);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbIface_sqlCmd(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqSqlVarArray *args, bool_t commit, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqSqlVar **arr = NULL;
	if (dbe == NULL || dbe->h_odbc == NULL) ERR_SET_OUT(errp, EPIPE);
	else if (args != NULL && (arr = args->get_array(args, &cnt, errp)) == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		if (Dz1TdqDbIface_sqlCmd_(dbe, query, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Command
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Insert
typedef struct Dz1TdqInsertEnv
{
	Dz1TdqSqlVarArray		 *args;
	Dz1TdqSqlVar			**arr;
	u32_t					  cnt;
} Dz1TdqInsertEnv;

static void Dz1TdqInsertEnv_del(Dz1TdqInsertEnv *p)
{
	if (p != NULL)
	{
		Dz1Memory_freeAndSetNull(&p->arr);
		Dz1TdqSqlVarArray_delAndSetNull(&p->args);
		Dz1Free(p);
	}
}

static void Dz1TdqInsertEnv_delAndSetNull(void *pptr)
{
	Dz1TdqInsertEnv **p = (Dz1TdqInsertEnv **)pptr;
	Dz1TdqInsertEnv_del(*p); *p = NULL;
}

static Dz1TdqInsertEnv *Dz1TdqInsertEnv_new(Dz1TdqColumnRefSeq *tgt_cols, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqInsertEnv *ret = (Dz1TdqInsertEnv *)Dz1Calloc(sizeof(Dz1TdqInsertEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqInsertEnv_delAndSetNull, (void *)&ret);
		if ((ret->args = Dz1TdqSqlVarArray_genFromSpec(tgt_cols, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->arr = ret->args->get_array(ret->args, &ret->cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqInsertEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static bool_t sql_insert_loop(HSTMT h_query, Dz1Str query, Dz1TdqInsertEnv *env, Dz1TdqRowSupplyF row_supply, void *user_ptr, Dz1Error *errp)
{
	RETCODE status = 0;
	bool_t done = FALSE;
	u32_t row_idx = 0;
	while(done == FALSE && errp->code == 0)
	{
		switch(row_supply(user_ptr, row_idx, env->arr, env->cnt, errp))
		{
		default:
		case Dz1TdqRowSupply_ok:
			if (HSTMT_paramArrayBind(h_query, env->arr, env->cnt, errp) == FALSE) ERR_OUT(errp);
			else if (_sqlCmdExecute(h_query, query, env->arr, env->cnt, errp) == FALSE) 
			{
				ERR_OUT(errp);
			}
			break;
		case Dz1TdqRowSupply_end:
			Dz1Error_set(errp, 0);
			done = TRUE;
			break;
		case Dz1TdqRowSupply_error:
			ERR_OUT(errp);
			break;
		}
		row_idx++;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbIface_insert(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqColumnRefSeq *tgt_cols, 
							Dz1TdqRowSupplyF row_supply, void *user_ptr, bool_t commit, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqInsertEnv *env = NULL;
	if (dbe == NULL || dbe->h_odbc == NULL) ERR_SET_OUT(errp, EPIPE);
	else if ((env = Dz1TdqInsertEnv_new(tgt_cols, errp)) == NULL) ERR_OUT(errp);
	else
	{
		HSTMT h_query;
		pthread_cleanup_push(Dz1TdqInsertEnv_delAndSetNull, (void *)&env);

		if (dbe_allocSqlStmt(dbe, &h_query, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			RETCODE status = 0;
			pthread_cleanup_push(_sql_alloc_stmt_cancel, (void *)h_query);
			if ((status = SQLPrepare(h_query, query, SQL_NTS)) != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) 
			{ 
				sql_error_print(h_query); 
				ERR_SET_OUT(errp, EFAULT); 
			}
//			else if (HSTMT_paramArrayBind(h_query, env->arr, env->cnt, errp) == FALSE) ERR_OUT(errp);
			else if (sql_insert_loop(h_query, query, env, row_supply, user_ptr, errp) == FALSE) ERR_OUT(errp);
			else
			{
				if (commit) SQLEndTran(SQL_HANDLE_DBC, dbe->h_odbc, SQL_COMMIT);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (_sql_alloc_stmt_cancel, (void *)h_query);
		}
		pthread_cleanup_pop(1); // (Dz1TdqInsertEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Insert
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Select Environment
typedef struct Dz1TdqSqlSelectEnv
{
	Dz1TdqSqlVarArray		*cols;
	Dz1TdqSqlVar		   **col_arr;
	SQLLEN					*col_stat_arr;
	u32_t					 col_cnt;

	Dz1TdqSqlVarArray		*args_ref;
	Dz1TdqSqlVar		   **arg_arr;
	u32_t					 arg_cnt;
} Dz1TdqSqlSelectEnv;

static void Dz1TdqSqlSelectEnv_del(Dz1TdqSqlSelectEnv *p)
{
	if (p != NULL)
	{
		Dz1TdqSqlVarArray_delAndSetNull(&p->cols);
		Dz1Memory_freeAndSetNull(&p->col_arr);
		Dz1Memory_freeAndSetNull(&p->col_stat_arr);

		Dz1Memory_freeAndSetNull(&p->arg_arr);
		Dz1Free(p);
	}
}

static void Dz1TdqSqlSelectEnv_delAndSetNull(void *pptr)
{
	Dz1TdqSqlSelectEnv **p = (Dz1TdqSqlSelectEnv **)pptr;
	Dz1TdqSqlSelectEnv_del(*p); *p = NULL;
}

static Dz1TdqSqlVarArray *_generate_var_arr(Dz1TdqQryRow *row_spec, Dz1TdqRow *alt_row_spec, Dz1Error *errp)
{
	Dz1TdqSqlVarArray *ret = NULL;
	if (row_spec != NULL)
	{
		if ((ret = Dz1TdqSqlVarArray_genFromSelSpec(row_spec, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (alt_row_spec != NULL)
	{
		if ((ret = Dz1TdqSqlVarArray_genFromSpec(alt_row_spec->seq, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else ERR_SET_OUT(errp, EINVAL);
	return ret;
}

static Dz1TdqSqlSelectEnv *Dz1TdqSqlSelectEnv_new(Dz1TdqQryRow *row_spec, Dz1TdqRow *alt_row_spec, Dz1TdqSqlVarArray *args_ref, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlSelectEnv *ret = (Dz1TdqSqlSelectEnv *)Dz1Calloc(sizeof(Dz1TdqSqlSelectEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlSelectEnv_delAndSetNull, (void *)&ret);
		if ((ret->cols = _generate_var_arr(row_spec, alt_row_spec, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->col_arr = ret->cols->get_array(ret->cols, &ret->col_cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->col_stat_arr = (SQLLEN *)Dz1Calloc(sizeof(SQLLEN), ret->col_cnt, errp)) == NULL) ERR_OUT(errp);
		else if (args_ref != NULL && (ret->arg_arr = args_ref->get_array(args_ref, &ret->arg_cnt, errp)) == NULL) ERR_OUT(errp);
		else 
		{
			ret->args_ref = args_ref;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlSelectEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Select Environment
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Select
static bool_t sql_select_rows_fetch_blob2buf(HSTMT h_query, u32_t col_idx, Dz1TdqSqlBlobFromDB *rfdb, SQLLEN len, Dz1Error *errp)
{
	RETCODE st;
	Dz1Binary2 *bin = NULL;
	Dz1Binary2_delAndSetNull(&rfdb->x.embedded);
	if ((rfdb->x.embedded = bin = Dz1Binary2_new(DZ1_BIN_DATA_ALLOC, (u32_t)len, errp)) == NULL) ERR_OUT(errp);
	else if ((st = SQLGetData(h_query, col_idx, SQL_C_BINARY, bin->data, bin->size, &len)) != SQL_SUCCESS)
	{
		ERR_SET_OUT(errp, EFAULT);
	}
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static void _file_creation_cancel(void *ptr)
{
	Dz1Str fn = (Dz1Str)ptr;
	if (fn && fn[0] != 0) Dz1File_delete(fn);
}

static bool_t sql_select_rows_fetch_blob2file(HSTMT h_query, u32_t col_idx, Dz1TdqSqlBlobFromDB *rfdb, SQLLEN len, Dz1Error *errp)
{
	RETCODE st;
	TCHAR temp[4096];
	Dz1Str fn = NULL;
	Dz1Stream *stp = NULL;
	Dz1Str_delAndSetNull(&rfdb->x.saved_file);
	if (Dz1GetTempFileName(fn, 4096, errp) == FALSE) ERR_OUT(errp);
	else if ((rfdb->x.saved_file = fn = Dz1Str_dup(temp, errp)) == NULL) ERR_OUT(errp);
	else if ((stp = Dz1Stream_openFile(fn, Dz1StreamFileMode_WR, errp)) == NULL) ERR_OUT(errp);
	else
	{
		u8_t *buf = (u8_t *)temp;
		size_t sz = sizeof(TCHAR) * 4096;
		pthread_cleanup_push(_file_creation_cancel, (void *)fn);
		pthread_cleanup_push(Dz1Stream_delAndSetNull, (void *)&stp);
		do 
		{
			if ((st = SQLGetData(h_query, col_idx, SQL_C_BINARY, buf, sz, &len)) != SQL_SUCCESS && st != SQL_SUCCESS_WITH_INFO)
			{
				sql_error_print(h_query);
				ERR_SET_OUT(errp, EFAULT);
				break;
			}
			else if (len > 0 && Dz1Stream_write(stp, buf, (size_t)len, errp) < 0)
			{
				ERR_OUT(errp);
				break;
			}
			else Dz1Error_set(errp, 0);
		} while (st == SQL_SUCCESS_WITH_INFO);
		pthread_cleanup_pop(1); // (Dz1Stream_delAndSetNull, (void *)&stp);
		pthread_cleanup_pop(errp->code); // (_file_creation_cancel, (void *)fn);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t sql_select_rows_fetch_blobs(HSTMT h_query, Dz1TdqSqlSelectEnv *env, Dz1Error *errp)
{
	u32_t i;
	Dz1TdqSqlVar *col = NULL;
	for (i = 0; i < env->col_cnt; i++)
	{
		col = env->col_arr[i];
		if ((col->present& 0xF0) == 0x40)
		{	// is Blob
			Dz1TdqSqlBlob *blob = col->x.blob;
			Dz1TdqSqlBlobFromDB *rfdb = blob->readFromDB;
			SQLLEN len = env->col_stat_arr[i];
			switch(rfdb->present)
			{
			default:
				rfdb->present = Dz1TdqSqlBlobFromDBPresent_embedded;
				rfdb->x.embedded = NULL;
			case Dz1TdqSqlBlobFromDBPresent_embedded:
				if (sql_select_rows_fetch_blob2buf(h_query, i + 1, rfdb, len, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1TdqSqlBlobFromDBPresent_saved_file:
				if (sql_select_rows_fetch_blob2file(h_query, i + 1, rfdb, len, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _sqlFetch(HSTMT h_query, Dz1TdqSqlSelectEnv *env, Dz1TdqRowTakeF row_taker, void *user_data, Dz1Error *errp)
{
	RETCODE status = 0;
	u32_t row_idx = 0;
	while(errp->code == 0)
	{
		if ((status = SQLFetch(h_query)) == SQL_SUCCESS)
		{
			row_taker(user_data, row_idx, env->col_arr, env->col_stat_arr, env->col_cnt);
			row_idx++;
		}
		else if (status == SQL_SUCCESS_WITH_INFO)
		{
			if (sql_select_rows_fetch_blobs(h_query, env, errp) == FALSE) ERR_OUT(errp);
			else
			{
				row_taker(user_data, row_idx, env->col_arr, env->col_stat_arr, env->col_cnt);
				row_idx++;
			}
		}
		else if (status == SQL_NO_DATA)
		{
			if (row_idx == 0) Dz1Error_set(errp, ENOENT);
			else Dz1Error_set(errp, 0);
			break;
		}
		else
		{
			Dz1Thread_printf(Dz1T("!!! Fetch Statue = %u\n"), status);
			sql_error_print(h_query);
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbIface_select(Dz1TdqDbIface *dbe, Dz1Str query, Dz1TdqQryRow *row_spec, Dz1TdqRow *alt_row_spec, 
							Dz1TdqRowTakeF row_taker, void *user_data, Dz1TdqSqlVarArray *args, Dz1Error *errp)
{
	Dz1TdqSqlSelectEnv *env = NULL;
	
	if ((row_spec == NULL && alt_row_spec == NULL) || row_taker == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((env = Dz1TdqSqlSelectEnv_new(row_spec, alt_row_spec, args, errp)) == NULL) ERR_OUT(errp);
	else
	{
		HSTMT h_query;
		pthread_cleanup_push(Dz1TdqSqlSelectEnv_delAndSetNull, (void *)&env);
		if (dbe_allocSqlStmt(dbe, &h_query, errp) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(_sql_alloc_stmt_cancel, (void *)h_query);

			if (HSTMT_columnArrayBind(h_query, env->col_arr, env->col_stat_arr, env->col_cnt, errp) == FALSE) ERR_OUT(errp);
			else if (HSTMT_paramArrayBind(h_query, env->arg_arr, env->arg_cnt, errp) == FALSE) ERR_OUT(errp);
			else if (_sqlCmdExecute(h_query, query, env->arg_arr, env->arg_cnt, errp) == FALSE) ERR_OUT(errp);
			else if (_sqlFetch(h_query, env, row_taker, user_data, errp) == FALSE) 
			{
				if (errp->code != ENOENT) ERR_OUT(errp);
			}
			else Dz1Error_set(errp, 0);

			Dz1TdqDbIface_commit(dbe, NULL);

			pthread_cleanup_pop(1); // (_sql_alloc_stmt_cancel, (void *)h_query);
		}
		pthread_cleanup_pop(1); // (Dz1TdqSqlSelectEnv_delAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Select
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1TdqDbIface_sqlPaging(Dz1ElasticBuf *dst, Dz1TdqPageSpec *spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR buf[64] = { 0, };
	u32_t offset = spec->pg_num * spec->pg_size;
	Dz1SNPRINTF(buf, 63, Dz1Text(" LIMIT %u, %u"), offset, spec->pg_size);
	ELB_PUSH_STR(dst, buf, errp);
	return TRUE;
}

bool_t Dz1TdqDbIface_commit(Dz1TdqDbIface *dbe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dbe == NULL || dbe->h_odbc == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
//		SQLRETURN status = SQLEndTran(SQL_HANDLE_ENV, dbe->h_db_env, SQL_COMMIT);
		SQLRETURN status = SQLEndTran(SQL_HANDLE_DBC, dbe->h_odbc, SQL_COMMIT);
		if (status != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) ERR_SET_OUT(errp, EFAULT);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1TdqDbIface_rollback(Dz1TdqDbIface *dbe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dbe == NULL || dbe->h_odbc == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
//		SQLRETURN status = SQLEndTran(SQL_HANDLE_ENV, dbe->h_db_env, SQL_ROLLBACK);
		SQLRETURN status = SQLEndTran(SQL_HANDLE_DBC, dbe->h_odbc, SQL_ROLLBACK);
		if (status != SQL_SUCCESS && status != SQL_SUCCESS_WITH_INFO) ERR_SET_OUT(errp, EFAULT);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

//static Dz1Error Dz1TdqDbIface_tblExist(Dz1TdqDbIface *dbe, Dz1TdqTblInstance *tbl, bool_t *ret_status)
static void _uint64_taker(void *user_ptr, u32_t row_idx, Dz1TdqSqlVar **src_arr, SQLLEN *src_stat_arr, u32_t src_cnt)
{
	bool_t *ret_status = (bool_t *)user_ptr;
	Dz1TdqSqlVar *v = src_arr[0];
	(*ret_status) = v->x.u64 ? TRUE : FALSE;
}

Dz1Error Dz1TdqDbIface_tblExist(Dz1TdqDbIface *dbe, Dz1Str tbl_name, bool_t *ret_status)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1TdqDbConnArg *arg = NULL;
	if (dbe == NULL || (arg = dbe->arg) == NULL || Dz1Str_isVoid(arg->dbn_opt) || Dz1Str_isVoid(tbl_name) || ret_status == NULL) 
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else
	{
		Dz1Str q = Dz1Text("SELECT COUNT(*) AS TBL_PRESENT FROM information_schema.tables WHERE table_schema=? AND table_name=?");
		Dz1TdqSqlVarArray *args = NULL;

		*ret_status = FALSE;

		if ((args = Dz1TdqSqlVarArray_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1TdqRow *row_spec = NULL;
			pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
			if (0) { }
			else if (Dz1TdqSqlVarArray_addStr(args, Dz1TdqSqlVarPresent_vtstring, arg->dbn_opt, errp) == FALSE) ERR_OUT(errp);
			else if (Dz1TdqSqlVarArray_addStr(args, Dz1TdqSqlVarPresent_vtstring, tbl_name, errp) == FALSE) ERR_OUT(errp);
			else if ((row_spec = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
			else 
			{
				pthread_cleanup_push(Dz1TdqRow_delAndSetNull, (void *)&row_spec);
				if (Dz1TdqRow_addNum(row_spec, Dz1Text("TBL_PRESENT"), Dz1TdqType_num_u64, NULL, NULL, errp) == FALSE) ERR_OUT(errp);
				else if (Dz1TdqDbIface_select(dbe, q, NULL, row_spec, _uint64_taker, (void *)ret_status, args, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				pthread_cleanup_pop(1); // (Dz1TdqQryRow_delAndSetNull, (void *)&row_spec);
			}
			pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
		}
	}
	return err;
}

#endif
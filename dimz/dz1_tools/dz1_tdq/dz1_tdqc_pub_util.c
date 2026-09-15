#include "dz1_tdqc_pub.h"

///////////////////////////////////////////////////////////////////////////////
// Dz1TdqcPubEnv
#define CURRENT_PATH						Dz1Text(".")
#define TEMPORARY_FILE_NAME					Dz1Text("_dz1_tdq_output_")

Dz1TdqcPubEnv *Dz1TdqcPubEnv_new(Dz1TdqcArg *arg, Dz1TdqcShapeList *list_ref, Dz1Error *errp)
{	// Temporary File Generation
	Dz1TdqcPubEnv *ret = (Dz1TdqcPubEnv *)Dz1Calloc(sizeof(Dz1TdqcPubEnv), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqcPubEnv_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (arg->output_hdr && (ret->hdr_fp = Dz1FileStream_open3(arg->dst_path_h, TEMPORARY_FILE_NAME, Dz1Text("h"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
		else if (arg->output_src && (ret->src_fp = Dz1FileStream_open3(arg->dst_path_c, TEMPORARY_FILE_NAME, Dz1Text("c"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->shapes = list_ref;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1TdqcPubEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1TdqcPubEnv_del(Dz1TdqcPubEnv *p)
{
	if (p != NULL)
	{
		Dz1FileStream_closeAndSetNull(&p->hdr_fp);
		Dz1FileStream_closeAndSetNull(&p->src_fp);
		Dz1Free(p);
	}
}
// Dz1TdqcPubEnv
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ColumnPubEnv
ColumnPubEnv *ColumnPubEnv_new(Dz1TdqColumnRefSeq *row_seq, StructMemberList *memb, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ColumnPubEnv *ret = NULL;
	if (row_seq == NULL || memb == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (ColumnPubEnv *)Dz1Calloc(sizeof(ColumnPubEnv), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ColumnPubEnv_delAndSetNull, (void *)&ret);
		if ((ret->col = row_seq->get_array(row_seq, &ret->col_cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->memb = memb->get_array(memb, &ret->memb_cnt, errp)) == NULL) ERR_OUT(errp);
		else if (ret->col_cnt != ret->memb_cnt) 
		{
			Dz1Thread_printf("Member Count mismatch col(%u), memb(%u)\n", ret->col_cnt, ret->memb_cnt);
			ERR_SET_OUT(errp, EFAULT);
		}
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (ColumnPubEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void ColumnPubEnv_del(ColumnPubEnv *p)
{
	if (p != NULL)
	{
		if (p->col != NULL) Dz1Free(p->col); 
		p->col = NULL;
		if (p->memb != NULL) Dz1Free(p->memb); 
		p->memb = NULL;
		Dz1Free(p);
	}
}

bool_t ColumnPubSupplyApi_pub(FILE *fp, ColumnPubEnv *env, ColumnPubSupplyApi *tbl, Dz1TdqcShapeOptList *opts, int tab, Dz1Error *errp)
{
	u32_t i;
	ColumnPubSupplyApi *api = NULL;
	Dz1TdqColumn *col = NULL;
	StructMemberEntry *memb = NULL;
	for (i = 0; i < env->col_cnt; i++)
	{
		col = env->col[i];
		memb = env->memb[i];
		if ((api = ColumnPubSupplyApi_find(tbl, col->sql_type->present)) == NULL) ERR_SET_OUT(errp, ENOSYS);
		else if (api->pub(fp, i, col, memb, opts, tab, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// ColumnPubEnv
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1TdqRowRef_pub_enumerate(FILE *fp, Dz1TdqRowRef *cols, Dz1Error *errp)
{
	u32_t cnt = 0;
	Dz1TdqColumn **arr = cols->seq->get_array(cols->seq, &cnt, errp);
	if (arr == NULL) ERR_OUT(errp);
	else
	{
		u32_t i;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
		for (i = 0; i < cnt; i++) Dz1Thread_fprintf(fp, ", Dz1Text(\"%s\")", arr[i]->name);
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

ColumnPubSupplyApi *ColumnPubSupplyApi_find(ColumnPubSupplyApi *tbl, Dz1TdqSqlTypeSpecPresent present)
{
	ColumnPubSupplyApi *i;
	for (i = tbl; i->present != Dz1TdqSqlTypeSpecPresent_max; i++)
		if (i->present == present) return i;
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// File Fix
static Dz1Error _file_fix(str_t dest_fn, str_t src_fn, str_t script_fn, bool_t doTouch)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	unlink(dest_fn);
	if (rename(src_fn, dest_fn) < 0)
	{	// 신규파일 이름변경 실패 -> 진행 불가
		unlink(src_fn);
		ERR_SET_OUT(&err, errno);
	}

#if 0
	str_t exist;
	if ((exist = Dz1TextFile_load0(dest_fn, NULL, &err)) == NULL)
	{	// 기존파일 읽기 실패
		if (err.code != ENOENT) ERR_OUT(&err);
		else
		{	// 기존 파일 없음 -> 이름 변경
			Dz1Error_set(&err, 0);
			if (rename(src_fn, dest_fn) < 0)
			{	// 이름 변경 실패-> 파일 삭제
				unlink(src_fn);
				ERR_SET_OUT(&err, errno);
			}
		}
	}
	else
	{	// 기존파일 읽기 성공
		str_t mine = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)exist);
		// 임시출력 File 읽기
		if ((mine = Dz1TextFile_load0(src_fn, NULL, &err)) == NULL)
		{	// 읽기 실패
			ERR_OUT(&err);
		}
		else
		{
			size_t mine_size, exist_size;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)mine);

			if ((mine_size = strlen(mine)) != (exist_size = strlen(exist)) || memcmp(mine, exist, mine_size) != 0)
			{	// 서로 다른 내용 -> unlink exist and rename mine
				Dz1Thread_printf("File Fixing... %s\n", dest_fn);
				if (unlink(dest_fn) < 0)
				{	// 기존 File 삭제 실패 -> 진행 불가
					ERR_SET_OUT(&err, errno);
				}
				else if (rename(src_fn, dest_fn) < 0)
				{	// 신규파일 이름변경 실패 -> 진행 불가
					unlink(src_fn);
					ERR_SET_OUT(&err, errno);
				}
			}
			else
			{	// 같은 내용 -> unlink mine, touch basis file
				Dz1Thread_printf("Nothing changed... %s\n", dest_fn);
				unlink(src_fn);
#ifndef UNIX_SYSTEM
				{
					// 기존 파일의 시간
					FILETIME tModDest, tModBasis;
					HANDLE f = CreateFile(dest_fn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					GetFileTime(f, NULL, NULL, &tModDest);
					CloseHandle(f);

					// basis 파일의 시간
					f = CreateFile(script_fn, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					GetFileTime(f, NULL, NULL, &tModBasis);

					Dz1Thread_printf("%s = %08X.%08X\n", dest_fn, tModDest.dwHighDateTime, tModDest.dwLowDateTime);
					Dz1Thread_printf("%s = %08X.%08X\n", script_fn, tModBasis.dwHighDateTime, tModBasis.dwLowDateTime);

					if (CompareFileTime(&tModDest, &tModBasis) < 0)
					{	// basis 파일의 시간을 dest_fn의 시간으로
						Dz1Thread_printf("Set File Time...\n");
						if (SetFileTime(f, NULL, &tModDest, &tModDest) == 0) ERR_SET_OUT(&err, GetLastError());
					}

					CloseHandle(f);
				}
#endif
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)mine);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)exist);
	}
#endif
	return err;
}

Dz1Error file_fix(Dz1Str dst_path, Dz1Str dst_name, Dz1Str dst_ext, Dz1Str script_path, Dz1Str script_name, Dz1Str script_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	char dest_fn[1024], src_fn[1024], script_fn[1024];
	if		((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, dest_fn), dst_path, dst_name, dst_ext)).code) ERR_OUT(errp);				// 출력 파일
	else if ((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, src_fn), dst_path, TEMPORARY_FILE_NAME, dst_ext)).code) ERR_OUT(errp);	// 임시 출력
	else if ((*errp = Dz1FileName_concatPathNameExt(Dz1ArrParam(char, script_fn), script_path, script_name, script_ext)).code) ERR_OUT(errp);	// 원본 스크립트
	else if ((*errp = _file_fix(dest_fn, src_fn, script_fn, TRUE)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}
// File Fix
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// HEADER Declare Name
typedef enum LetterFlag
{
	LetterFlag_none,
	LetterFlag_alphaU,
	LetterFlag_alphaL,
	LetterFlag_digit,
	LetterFlag_underbar,
	LetterFlag_else
} LetterFlag;

static LetterFlag _get_flag(char c)
{
	LetterFlag ret = LetterFlag_none;
	if (isdigit(c)) ret = LetterFlag_digit;
	else if (isalpha(c))
	{
		if (c >= 'a' && c <= 'z') ret = LetterFlag_alphaL;
		else ret = LetterFlag_alphaU;
	}
	else if (c == '_') ret = LetterFlag_underbar;
	else ret = LetterFlag_else;
	return ret;
}

static bool_t ins_arr[6][6] = 
{//	  N  U  L  D  B  E
	{ 0, 0, 0, 0, 0, 0 },	// None
	{ 0, 0, 0, 1, 0, 1 },	// Upper
	{ 0, 1, 0, 1, 0, 1 },	// Lower
	{ 0, 1, 1, 0, 0, 1 },	// Digit
	{ 0, 0, 0, 0, 0, 0 },	// underBar
	{ 0, 1, 1, 1, 0, 0 }	// Else
};

void _mk_dcl_name(char *dst, char *src)
{
	LetterFlag prev_flag = LetterFlag_none, flag = LetterFlag_none;
	char *dp = dst, *cp = src;
	while(*cp)
	{
		flag = _get_flag(*cp);
		if (ins_arr[prev_flag][flag]) *dp++ = '_';
		*dp++ = Dz1Letter_ucase(*cp);
		prev_flag = flag;
		cp++;
	}
	*dp++ = 0;
}
// HEADER Declare Name
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Module Name
void _get_mod_name(char dst[1024], str_t src)
{
	char *cp = strrchr(src, DIR_SEP_A);
	if (cp == NULL) strcpy(dst, src);
	else
	{
		cp++;
		strcpy(dst, cp);
		if ((cp = strrchr(dst, '.')) != NULL) *cp = 0;
	}
}
// Module Name
///////////////////////////////////////////////////////////////////////////////

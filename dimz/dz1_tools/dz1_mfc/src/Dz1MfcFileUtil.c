//#include "stdafx.h"
#include <codeconv.h>
#include <dz1_thread_stdio.h>
#include "Dz1MfcFileUtil.h"

void Dz1MfcFileEntry_ucase(Dz1MfcFileEntry *node)
{
	if (node == NULL) { }
	else
	{
		if (node->name_ext != NULL && node->name_ext[0] != 0) Dz1Str_ucase(node->name_ext);
		if (node->name != NULL && node->name[0] != 0) Dz1Str_ucase(node->name);
		if (node->ext != NULL && node->ext[0] != 0) Dz1Str_ucase(node->ext);
	}
}

void Dz1MfcFileEntry_lcase(Dz1MfcFileEntry *node)
{
	if (node == NULL) { }
	else
	{
		if (node->name_ext != NULL && node->name_ext[0] != 0) Dz1Str_lcase(node->name_ext);
		if (node->name != NULL && node->name[0] != 0) Dz1Str_lcase(node->name);
		if (node->ext != NULL && node->ext[0] != 0) Dz1Str_lcase(node->ext);
	}
}

bool_t Dz1MfcFileList_addDirEntry(Dz1MfcFileList *dst, Dz1DirEntry *entry, bool_t ucase, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFileEntry *node = NULL;
	if ((node = Dz1MfcFileEntry_new(entry->name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileEntry_delAndSetNull, (void *)&node);
		if (ucase) Dz1MfcFileEntry_ucase(node);

		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
			ret = TRUE;
		}
		pthread_cleanup_pop(1); // (Dz1MfcFileEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

Dz1MfcFileList *Dz1MfcFileList_fromPath(Dz1Str path, bool_t ucase, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFileList *ret = NULL;
	if (path == NULL || path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1MfcFileList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1DirCatalog *cat = NULL;
		pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&ret);
		if ((cat = Dz1DirCatalog_newFiles(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&cat);
			for (i = 0; errp->code == 0 && i < cat->valid; i++)
			{
				if (Dz1MfcFileList_addDirEntry(ret, &cat->entries[i], ucase, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&cat);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MfcFileList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1MfcFileEntry *Dz1MfcFileList_findByNameExt(Dz1MfcFileList *list, Dz1Str name_ext)
{
	Dz1MfcFileEntry *ret = NULL;
	if (list != NULL && name_ext != NULL && name_ext[0] != 0)
	{
		Dz1MfcFileEntry key = { name_ext };
		ret = list->find(list, &key);
	}
	return ret;
}

Dz1MfcFileOperRenameEntry *Dz1MfcFileOperRenameList_findByNameExt(Dz1MfcFileOperRenameList *list, Dz1Str name_ext)
{
	Dz1MfcFileEntry file_key = { name_ext };
	Dz1MfcFileOperRenameEntry key = { &file_key };
	return list->find(list, &key);
}

static Dz1MfcFileOperCopyCollision *Dz1MfcFileOperCopyCollision_newFromFile(Dz1Str name_ext, Dz1Str src_path, Dz1Str dst_path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFileOperCopyCollision *ret = Dz1MfcFileOperCopyCollision_new(0, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&ret);

		if ((ret->src_size = Dz1File_getSize2(src_path, name_ext)) < 0) ERR_SET_OUT(errp, EFAULT);
		else if ((ret->dst_size = Dz1File_getSize2(dst_path, name_ext)) < 0) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1MfcFileOperCopyCollision_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error Dz1MfcFileOperCopyList_append(Dz1MfcFileOperCopyList *dst, Dz1Str file_name_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcFileOperCopyEntry *node = Dz1MfcFileOperCopyEntry_new(NULL, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&node);
		if ((node->file = Dz1MfcFileEntry_new(file_name_ext, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcFileOperCopyEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1Error Dz1MfcFileOperCopyData_append(Dz1MfcFileOperCopyData *dst, Dz1Str file_name_ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || file_name_ext == NULL || file_name_ext[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1MfcFileOperCopyList_append(dst->files, file_name_ext)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

typedef struct FileSimpleOperArg
{
	void						*opt;
	bool_t						 ret;
	u32_t						 idx;
	u32_t						 total;
//	Dz1MfcFileSimpleOperCBF		 cb;
//	void						*cb_param;
} FileSimpleOperArg;

///////////////////////////////////////////////////////////////////////////////
// Delete
bool_t Dz1MfcFileDelete(Dz1MfcFileOperDeleteEntry *p)
{
	bool_t ret = TRUE;
	if (p->state != Dz1MfcFileOperState_success)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		Dz1MfcFileEntry *file = p->file;
		if ((*errp = Dz1File_delete2(p->path, file->name_ext)).code)
		{
			ERR_OUT(errp);
			p->state = Dz1MfcFileOperState_fail;
			p->fail_code = errp->code;
			Dz1Error_set(errp, 0);
			ret = FALSE;
		}
		else p->state = Dz1MfcFileOperState_success;
	}
	return ret;
}

static Dz1Error FileDelete(void *ptr, Dz1MfcFileOperDeleteEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	FileSimpleOperArg *arg = (FileSimpleOperArg *)ptr;
	Dz1MfcFileOperDeleteData *data = arg->opt;
	if (Dz1MfcFileDelete(p) == FALSE)
	{
		data->failed->add(data->failed, p);
		arg->ret = FALSE;
	}

	return err;
}

static Dz1Error Dz1MfcFilesDelete_prepare(Dz1MfcFileOperDeleteData *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (data->failed->count(data->failed) > 0)
	{
		Dz1MfcFileOperDelRefList_delAndSetNull(&data->failed);
		if ((data->failed = Dz1MfcFileOperDelRefList_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

bool_t Dz1MfcFilesDelete(Dz1MfcFileOperDeleteData *data)
{
	FileSimpleOperArg arg = { data, TRUE, 0, 0 };
	if (data != NULL && (arg.total = data->list->count(data->list)) > 0)
	{
		DZ1_ERROR_SAFE_VAR(errp, err);
		if ((*errp = Dz1MfcFilesDelete_prepare(data)).code) ERR_OUT(errp);
		else data->list->travel(data->list, FileDelete, (void *)&arg);
	}
	return arg.ret;
}
// Delete
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Rename
static bool_t _rename_append_files(Dz1MfcFileList *dst, Dz1DirEntry *entry, Dz1Error *errp)
{	// catalog entry를 대문자로 만들어 추가
	bool_t ret = FALSE;
	Dz1MfcFileEntry *node = Dz1MfcFileEntry_new(entry->name, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileEntry_delAndSetNull, (void *)&node);
		Dz1Str_ucase(node->name_ext);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcFileEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

static bool_t _rename_chk_and_add(Dz1MfcFileList *dst, Dz1MfcFileOperRenameList *list, Dz1DirEntry *entry, Dz1Error *errp)
{	// catalog entry가 원본 목록에 없으면 추가
	bool_t ret = FALSE;
	if (Dz1MfcFileOperRenameList_findByNameExt(list, entry->name) == NULL)
	{	
		if (_rename_append_files(dst, entry, errp) == FALSE) ERR_OUT(errp);
		else ret = TRUE;
	}
	else ret = TRUE;
	return ret;
}

static Dz1MfcFileList *_rename_Dz1MfcFileList_fromPath(Dz1Str path, Dz1MfcFileOperRenameList *list, Dz1Error *err)
{	// 특정 경로로 부터 원본목록에 등록되지 않은 파일의 목록을 만든다. 목록의 파일명은 모두 대문자로 만든다.
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFileList *ret = Dz1MfcFileList_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1DirCatalog *cat = NULL;
		pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&ret);
		if ((cat = Dz1DirCatalog_newFiles(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&cat);
			for (i = 0; errp->code == 0 && i < cat->valid; i++)
			{
				if (_rename_chk_and_add(ret, list, &cat->entries[i], errp) == FALSE) ERR_OUT(errp);
			}
			pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&cat);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MfcFileList_delAndSetNull, (void *)&ret);
	}
	return ret;
}


static Dz1Error RenameChkSameName(void *ptr, Dz1MfcFileOperRenameEntry *p)
{	// 동일한 이름을 가지는 항목은 미리 success로 만들기
	u32_t *initials = (u32_t *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (p->state == Dz1MfcFileOperState_initial)
	{
		Dz1MfcFileEntry *src = p->src, *dst = p->dst;
		if (Dz1MfcFileEntry_cmp(src, dst) == 0)
			p->state = Dz1MfcFileOperState_success;
		else (*initials)++;
	}
	return err;
}

typedef struct RenameChkDstNameArg
{
	s32_t						 cnt;
	Dz1MfcFileList				*origin;
	Dz1MfcFileOperRenRefList	*failed;
} RenameChkDstNameArg;

static Dz1Error _rename_chk_dst_name(void *ptr, Dz1MfcFileOperRenameEntry *p)
{	// 변경후의 이름이 기존 파일과 충돌하는지 검사
	DZ1_ERROR_SAFE_VAR(errp, err);
	RenameChkDstNameArg *arg = (RenameChkDstNameArg *)ptr;

	Dz1MfcFileEntry *dst = p->dst;
	Dz1Str temp = Dz1Str_dup(dst->name_ext, errp);
	if (temp == NULL) { ERR_OUT(errp); arg->cnt = -1; }
	else
	{
		Dz1MfcFileList *origin = arg->origin;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);

		Dz1Str_ucase(temp);
		if (Dz1MfcFileList_findByNameExt(origin, temp) != NULL)
		{
			arg->failed->add(arg->failed, p);

			p->state = Dz1MfcFileOperState_fail;
			p->fail_code = EEXIST;
			arg->cnt++;
		}

		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
	}
	return err;
}

static s32_t _rename_chk_dst_names(Dz1MfcFileOperRenameDstIndex *index, Dz1MfcFileList *origin, Dz1MfcFileOperRenRefList *failed, Dz1Error *errp)
{	// 변경후의 이름들이 기존 파일과 충돌하는지 검사
	RenameChkDstNameArg arg = { 0, origin, failed };
	if ((*errp = index->travel(index, _rename_chk_dst_name, (void *)&arg)).code) ERR_OUT(errp);
	return arg.cnt;
}

static Dz1Error _rename_to_mediate(void *ptr, Dz1MfcFileOperRenameEntry *p)
{	// 서로 충돌이 없도록 사전 변경
	FileSimpleOperArg *arg = (FileSimpleOperArg *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->state == Dz1MfcFileOperState_initial)
	{
		Dz1MfcFileEntry *src = p->src;
		Dz1Str path = (Dz1Str)arg->opt;

		TCHAR mediate_name[4096] = Dz1Text("_###_mediate_###_.");
		Dz1STRCAT(mediate_name, src->name_ext);

		if ((*errp = Dz1File_rename2(path, mediate_name, path, src->name_ext)).code)
		{
			ERR_OUT(errp);
			p->state = Dz1MfcFileOperState_fail;
			p->fail_code = errp->code;
			Dz1Error_set(errp, 0);
			arg->ret = FALSE;
		}
		else
		{
			p->state = Dz1MfcFileOperState_prepared;
			p->fail_code = 0;
		}
	}

//	if (arg->cb != NULL) arg->cb(arg->cb_param, 0, arg->idx, arg->total, (void *)p);
	arg->idx++;

	return err;
}

static Dz1Error _rename_to_dst(void *ptr, Dz1MfcFileOperRenameEntry *p)
{	// 최종 목적 명칭으로 변경
	FileSimpleOperArg *arg = (FileSimpleOperArg *)ptr;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->state == Dz1MfcFileOperState_prepared)
	{
		Dz1MfcFileEntry *src = p->src;
		Dz1MfcFileEntry *dst = p->dst;
		Dz1Str path = (Dz1Str)ptr;
		TCHAR mediate_name[4096] = Dz1Text("_###_mediate_###_.");
		Dz1STRCAT(mediate_name, src->name_ext);

		if ((*errp = Dz1File_rename2(path, dst->name_ext, path, mediate_name)).code)
		{
			ERR_OUT(errp);
			p->state = Dz1MfcFileOperState_fail;
			p->fail_code = errp->code;
			Dz1Error_set(errp, 0);
			arg->ret = FALSE;
		}
		else
		{
			p->state = Dz1MfcFileOperState_success;
			p->fail_code = 0;
		}
	}

//	if (arg->cb != NULL) arg->cb(arg->cb_param, 1, arg->idx, arg->total, (void *)p);
	arg->idx++;

	return err;
}

static Dz1Error Dz1MfcFilesRename_prepare(Dz1MfcFileOperRenameData *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (data->failed->count(data->failed) > 0)
	{
		Dz1MfcFileOperRenRefList_delAndSetNull(&data->failed);
		if ((data->failed = Dz1MfcFileOperRenRefList_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

bool_t Dz1MfcFilesRename(Dz1MfcFileOperRenameData *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	FileSimpleOperArg arg = { (void *)data, TRUE, 0, 0 };
	if (data != NULL && data->list != NULL && (arg.total = data->list->count(data->list)) > 0)
	{
		u32_t initials = 0;

		Dz1MfcFileOperRenameList *list = data->list;
		list->travel(list, RenameChkSameName, (void *)&initials);									// 같은 이름은 미리 패스

		if (initials > 0)
		{	// 바꿀 항목이 있으면
			Dz1MfcFileList *origin = NULL;
			
			// 대상 폴더에 목록 작성
			if ((*errp = Dz1MfcFilesRename_prepare(data)).code) ERR_OUT(errp);
			else if ((origin = _rename_Dz1MfcFileList_fromPath(data->path, data->list, errp)) == NULL) ERR_OUT(errp);
			else
			{
				s32_t collision = 0;
				pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&origin);
				collision = _rename_chk_dst_names(data->index, origin, data->failed, errp);			// 바꿀 이름이 기존 항목과 충돌하는지 검사
				pthread_cleanup_pop(1); // (Dz1MfcFileList_delAndSetNull, (void *)&origin);

				if (collision < 0) ERR_OUT(errp);
				else if (collision > 0) ERR_SET_OUT(errp, EEXIST);
				else // if (collision == 0)
				{
					bool_t med_status = FALSE, final_status = FALSE;

					arg.ret = TRUE; arg.idx = 0;
					list->travel(list, _rename_to_mediate, (void *)&arg);
					med_status = arg.ret;

					arg.ret = TRUE; arg.idx = 0;
					list->travel(list, _rename_to_dst, (void *)&arg);
					final_status = arg.ret;

					arg.ret = med_status && final_status ? TRUE : FALSE;
				}
			}
		}
	}
	return arg.ret;
}
// Rename
///////////////////////////////////////////////////////////////////////////////


















static Dz1Error Dz1MfcFileOperCopyData_prepare(Dz1MfcFileOperCopyData *data)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (data == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (data->failed != NULL)
		{
			if (data->failed->count(data->failed) > 0)
			{	// flush
				Dz1MfcFileOperCopyRefList_delAndSetNull(&data->failed);
				if ((data->failed = Dz1MfcFileOperCopyRefList_new(errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		// data->failed == NULL
		else if ((data->failed = Dz1MfcFileOperCopyRefList_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Dz1MfcFileOperCopyData Collision Check
typedef struct CopyDataTravelArg
{
	bool_t					 ret;
	Dz1MfcFileOperCopyData	*data;
	Dz1MfcFileList			*ucased_dest;

	Dz1MfcFileCopyOperCBF	 cb;
	void					*cb_arg;
} CopyDataTravelArg;

static Dz1Error CopyData_chk_collision(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CopyDataTravelArg *arg = (CopyDataTravelArg *)ptr;
	Dz1MfcFileOperCopyData *data = arg->data;
	if (p->state == Dz1MfcFileOperState_initial)
	{
		Dz1MfcFileEntry *file = p->file;
		Dz1Str temp = Dz1Str_dup(file->name_ext, errp);
		if (temp == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&temp);

			Dz1Str_ucase(temp);
			if (Dz1MfcFileList_findByNameExt(arg->ucased_dest, temp) != NULL)
			{
				if ((p->collision = Dz1MfcFileOperCopyCollision_newFromFile(file->name_ext, data->src_path, data->dst_path, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->failed->add(data->failed, p);

					p->state = Dz1MfcFileOperState_fail;
					p->fail_code = EEXIST;
					arg->ret = TRUE;
					Dz1Error_set(errp, 0);

					if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_PREPARE, 0, (void *)p);
				}
			}
			else
			{
				p->total = Dz1File_getSize2(data->src_path, file->name_ext);
				data->total += p->total;

				p->state = Dz1MfcFileOperState_prepared;
				Dz1Error_set(errp, 0);
			}

			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&temp);
		}
	}
	return err;
}

static bool_t _Dz1MfcFileOperCopyData_is_collision(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CopyDataTravelArg arg = { FALSE, data, NULL, cb, cb_param };
	if ((arg.ucased_dest = Dz1MfcFileList_fromPath(data->dst_path, TRUE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MfcFileOperCopyList *files = data->files;
		pthread_cleanup_push(Dz1MfcFileList_delAndSetNull, (void *)&arg.ucased_dest);

		files->travel(files, CopyData_chk_collision, (void *)&arg);

		pthread_cleanup_pop(1); // (Dz1MfcFileList_delAndSetNull, (void *)&arg.ucased_dest);
	}
	return arg.ret;
}

bool_t Dz1MfcFileOperCopyData_is_collision(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;
	if (data == NULL || data->files == NULL || data->files->count(data->files) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1MfcFileOperCopyData_prepare(data)).code) ERR_OUT(errp);	// initialize failed file list
	else ret = _Dz1MfcFileOperCopyData_is_collision(data, cb, cb_param);

	return ret;
}
// Dz1MfcFileOperCopyData Collision Check
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Copy with code-set free
typedef struct CopyCbArg
{
	Dz1MfcFileOperCopyEntry *entry;
	Dz1MfcFileCopyOperCBF	 cb;
	void					*cb_arg;
} CopyCbArg;

static DWORD CALLBACK copy_cb(LARGE_INTEGER TotalFileSize, LARGE_INTEGER TotalBytesTransferred,
							  LARGE_INTEGER StreamSize, LARGE_INTEGER StreamBytesTransferred,
							  DWORD dwStreamNumber, DWORD dwCallbackReason, HANDLE hSourceFile, HANDLE hDestinationFile,
							  LPVOID lpData)
{	// always single file copy
	CopyCbArg *arg = (CopyCbArg *)lpData;
	Dz1MfcFileOperCopyEntry *entry = arg->entry;

	s64_t tfs = TotalFileSize.QuadPart;
	s64_t tbt = TotalBytesTransferred.QuadPart;
	s64_t ss = StreamSize.QuadPart;
	s64_t sbt = StreamBytesTransferred.QuadPart;

	Dz1Thread_printf(Dz1T("copy_cb() : N=%u, R=%s TFS=") DZ1_FMT64U Dz1T(" TBT=") DZ1_FMT64U Dz1T(" SS=") DZ1_FMT64U Dz1T(" SBT=") DZ1_FMT64U Dz1T("\n"),
					dwStreamNumber, dwCallbackReason == CALLBACK_STREAM_SWITCH ? Dz1T("switched") : Dz1T("chunk"), tfs, tbt, ss, sbt);

	if (dwCallbackReason == CALLBACK_STREAM_SWITCH)
	{
//		entry->total = (u64_t)TotalFileSize.QuadPart;
		entry->copied = 0;
	}
	else if (dwCallbackReason == CALLBACK_CHUNK_FINISHED)
	{
		// entry->total = (u64_t)TotalFileSize.QuadPart;
		entry->copied = tbt;
	}

	if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_TRANSFER, DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_CHUNK_DONE, (void *)entry);

	return PROGRESS_CONTINUE;
}


static int CopyFileExCodeFree(TCHAR *src, TCHAR *dst, CopyCbArg *cb_arg)
{
	int ret = 0;
#ifndef UNICODE
	// ANSI version
	wchar_t src_fn[4096], dst_fn[4096];
	Dz1CodeConv((u8_t *)src_fn, sizeof(wchar_t) * 4096, WINDOWS_UNICODE, (u8_t *)src, strlen(src), "EUC-KR");
	Dz1CodeConv((u8_t *)dst_fn, sizeof(wchar_t) * 4096, WINDOWS_UNICODE, (u8_t *)dst, strlen(dst), "EUC-KR");
	if (CopyFileExW(src_fn, dst_fn, copy_cb, cb_arg, FALSE, 0) == 0)
		ret = GetLastError();
#else
	// UNICODE version
	if (CopyFileExW(src, dst, copy_cb, cb_arg, FALSE, 0) == 0)
		ret = GetLastError();
 #endif
	return ret;
}
// File Copy with code-set free
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Copy
static Dz1Error _FilesCopy(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->state == Dz1MfcFileOperState_prepared)
	{
		Dz1MfcFileEntry *file = p->file;

		CopyDataTravelArg *arg = (CopyDataTravelArg *)ptr;
		Dz1MfcFileOperCopyData *data = arg->data;

		TCHAR *src_fn = Dz1Calloc(sizeof(TCHAR), 4096, NULL);
		TCHAR *dst_fn = Dz1Calloc(sizeof(TCHAR), 4096, NULL);

		if ((*errp = Dz1FileName_concatPathName(src_fn, 4096, data->src_path, file->name_ext)).code) ERR_OUT(errp);
		else if ((*errp = Dz1FileName_concatPathName(dst_fn, 4096, data->dst_path, file->name_ext)).code) ERR_OUT(errp);
		else
		{
			int status = 0;
			CopyCbArg copy_arg = { p, arg->cb, arg->cb_arg };

			if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_TRANSFER, DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_START, (void *)p);

			if ((status = CopyFileExCodeFree(src_fn, dst_fn, &copy_arg)) != 0)
			{	// 복사 실패
				data->failed->add(data->failed, p);

				p->state = Dz1MfcFileOperState_fail;
				p->fail_code = status;
				arg->ret = FALSE;
				ERR_SET_OUT(errp, status);
			}
			else
			{	// 복사 성공
				p->state = Dz1MfcFileOperState_success;
				p->fail_code = status;
				Dz1Error_set(errp, 0);
			}

			data->copied += p->total;

			if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_TRANSFER, DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_DONE, (void *)p);
		}
		Dz1Free(src_fn);
		Dz1Free(dst_fn);
	}
	return err;
}

bool_t Dz1MfcFilesCopy(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	CopyDataTravelArg arg = { TRUE, data, NULL, cb, cb_arg };
	if (data == NULL || data->files == NULL || data->files->count(data->files) == 0) { ERR_SET_OUT(errp, EINVAL); arg.ret = FALSE; }
	else if ((*errp = Dz1MfcFileOperCopyData_prepare(data)).code) { ERR_OUT(errp); arg.ret = FALSE; }
	else if (_Dz1MfcFileOperCopyData_is_collision(data, cb, cb_arg) == TRUE) { ERR_SET_OUT(errp, EEXIST); arg.ret = FALSE; }
	else if ((*errp = data->files->travel(data->files, _FilesCopy, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return arg.ret;
}

bool_t Dz1MfcFileCopy(Dz1Str src_path, Dz1Str dst_path, Dz1Str file_name_ext, Dz1MfcFileCopyOperCBF cb, void *cb_arg)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t ret = FALSE;
	Dz1MfcFileOperCopyData *data = NULL;
	
	if (src_path == NULL || src_path[0] == 0 || dst_path == NULL || dst_path[0] == 0 || file_name_ext == NULL || file_name_ext[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((data = Dz1MfcFileOperCopyData_new(src_path, dst_path, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyData_delAndSetNull, (void *)&data);

		if ((*errp = Dz1MfcFileOperCopyList_append(data->files, file_name_ext)).code) ERR_OUT(errp);
		else if (Dz1MfcFilesCopy(data, cb, cb_arg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1MfcFileOperCopyData_delAndSetNull, (void *)&data);
	}
	return ret;
}
// Copy
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Move
static int MoveFileExCodeFree(TCHAR *src, TCHAR *dst, CopyCbArg *cb_arg)
{
	int ret = 0;
#ifndef UNICODE
	// ANSI version
	wchar_t src_fn[4096], dst_fn[4096];
	Dz1CodeConv((u8_t *)src_fn, sizeof(wchar_t) * 4096, WINDOWS_UNICODE, (u8_t *)src, strlen(src), "EUC-KR");
	Dz1CodeConv((u8_t *)dst_fn, sizeof(wchar_t) * 4096, WINDOWS_UNICODE, (u8_t *)dst, strlen(dst), "EUC-KR");
	if (MoveFileWithProgressW(src_fn, dst_fn, copy_cb, cb_arg, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) == 0)
		ret = GetLastError();
#else
	// UNICODE version
	if (MoveFileWithProgressW(src, dst, copy_cb, cb_arg, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) == 0)
		ret = GetLastError();
#endif
	return ret;
}

static Dz1Error _FilesMove(void *ptr, Dz1MfcFileOperCopyEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (p->state == Dz1MfcFileOperState_prepared)
	{
		Dz1MfcFileEntry *file = p->file;

		CopyDataTravelArg *arg = (CopyDataTravelArg *)ptr;
		Dz1MfcFileOperCopyData *data = arg->data;

		TCHAR *src_fn = Dz1Calloc(sizeof(TCHAR), 4096, NULL);
		TCHAR *dst_fn = Dz1Calloc(sizeof(TCHAR), 4096, NULL);

		if ((*errp = Dz1FileName_concatPathName(src_fn, 4096, data->src_path, file->name_ext)).code) ERR_OUT(errp);
		else if ((*errp = Dz1FileName_concatPathName(dst_fn, 4096, data->dst_path, file->name_ext)).code) ERR_OUT(errp);
		else
		{
			int status = 0;
			CopyCbArg copy_arg = { p, arg->cb, arg->cb_arg };

			if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_TRANSFER, DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_START, (void *)p);

			if ((status = MoveFileExCodeFree(src_fn, dst_fn, &copy_arg)) != 0)
			{	// 이동 실패
				data->failed->add(data->failed, p);

				p->state = Dz1MfcFileOperState_fail;
				p->fail_code = status;
				arg->ret = FALSE;
				ERR_SET_OUT(errp, status);
			}
			else
			{	// 이동 성공
				p->state = Dz1MfcFileOperState_success;
				p->fail_code = 0;

				Dz1Error_set(errp, 0);
			}

			data->copied += p->total;

			if (arg->cb != NULL) arg->cb(arg->cb_arg, DZ1_FILE_COPY_PHASE_TRANSFER, DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_DONE, (void *)p);
		}
		Dz1Free(src_fn);
		Dz1Free(dst_fn);
	}
	return err;
}

bool_t Dz1MfcFilesMove(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	CopyDataTravelArg arg = { TRUE, data, NULL, cb, cb_arg };
	if (data == NULL || data->files == NULL || data->files->count(data->files) == 0) { ERR_SET_OUT(errp, EINVAL); arg.ret = FALSE; }
	else if ((*errp = Dz1MfcFileOperCopyData_prepare(data)).code) { ERR_OUT(errp); arg.ret = FALSE; }
	else if (_Dz1MfcFileOperCopyData_is_collision(data, cb, cb_arg) == TRUE) { ERR_SET_OUT(errp, EEXIST); arg.ret = FALSE; }
	else if ((*errp = data->files->travel(data->files, _FilesMove, (void *)&arg)).code) { ERR_OUT(errp); arg.ret = FALSE; }
	else Dz1Error_set(errp, 0);

	return arg.ret;

	//MoveFileWithProgress();
	return ret;
}

bool_t Dz1MfcFileMove(Dz1Str src_path, Dz1Str dst_path, Dz1Str file_name_ext, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	bool_t ret = FALSE;
	Dz1MfcFileOperCopyData *data = NULL;
	if (src_path == NULL || src_path[0] == 0 || dst_path == NULL || dst_path[0] == 0 || file_name_ext == NULL || file_name_ext[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((data = Dz1MfcFileOperCopyData_new(src_path, dst_path, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFileOperCopyData_delAndSetNull, (void *)&data);

		if ((*errp = Dz1MfcFileOperCopyList_append(data->files, file_name_ext)).code) ERR_OUT(errp);
		else if (Dz1MfcFilesMove(data, cb, cb_arg, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1MfcFileOperCopyData_delAndSetNull, (void *)&data);
	}
	return ret;
}
// Move
///////////////////////////////////////////////////////////////////////////////

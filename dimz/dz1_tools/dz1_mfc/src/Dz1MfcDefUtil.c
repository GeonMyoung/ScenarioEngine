#include "Dz1MfcDefUtil.h"
#include <ShellAPI.h>
#pragma comment(lib, "shell32.lib")

Dz1Error Dz1MfcLanManPathList_add_host(Dz1MfcLanManPathList *dst, Dz1Str name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcLanManPathEntry *node = NULL;
	if (dst == NULL || name == NULL || Dz1STRLEN(name) == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1MfcLanManPathEntry_new(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

void Dz1MfcLanManPathList_remove_host(Dz1MfcLanManPathList *dst, Dz1Str name)
{
	if (dst != NULL && name != NULL && Dz1STRLEN(name) > 0)
	{
		Dz1MfcLanManPathEntry key = { name };
		dst->remove(dst, &key);
	}
}

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathEntry CODEC
// static Dz1MfcLanManPathEntry *Dz1MfcLanManPathEntry_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1MfcLanManPathEntry *ret = Dz1MfcLanManPathEntry_new(NULL, errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static ssize_t Dz1MfcLanManPathEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcLanManPathEntry *src = (Dz1MfcLanManPathEntry *)_src;
	if (dst == NULL || src == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_write(dst, src->name, ed, param, errp), errp);
	}
	return ret;
}

static ssize_t Dz1MfcLanManPathEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcLanManPathEntry *dst = (Dz1MfcLanManPathEntry *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_OUT_RET(errp, EINVAL, -1);
	else if (Dz1Stream_eof(src) == TRUE) ERR_SET_OUT_RET(errp, E2BIG, -1);
	else
	{
		DZ1_IO_STREAM_FUNC(ret, Dz1Str_read(&dst->name, src, ed, param, errp), errp);
		// DZ1_STREAM_READ(dst->some_ptr, len, src, errp, ret);
		// DZ1_STREAM_READ4(dst->some_ptr, src, ed, errp, ret);
	}
	return ret;
}
// Dz1MfcLanManPathEntry CODEC
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathList Stream Read/Write
// static Dz1MfcLanManPathList *Dz1MfcLanManPathList_gen(Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_DECLARE(errp, err);
// 	Dz1MfcLanManPathList *ret = Dz1MfcLanManPathList_new(errp);
// 	if (ret == NULL) ERR_OUT(errp);
// 	return ret;
// }

static Dz1Error _Dz1MfcLanManPathList_write(void *ptr, Dz1MfcLanManPathEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1ListStreamArg *arg = (Dz1ListStreamArg *)ptr;
	ssize_t status = Dz1MfcLanManPathEntry_write(arg->stream, p, arg->ed, arg->option, errp);
	if (status < 0) ERR_OUT(errp);
	else arg->ret += status;
	return err;
}

ssize_t Dz1MfcLanManPathList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MfcLanManPathList *src = (Dz1MfcLanManPathList *)_src;
	if (src == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		ssize_t sz = sizeof(TCHAR);

		Dz1ListStreamArg arg = { dst, 0, ed, param };
		u16_t cnt = src->count(src);
		DZ1_STREAM_WRITE4(dst, (u32_t)(sz & 0xFFFFFFFF), ed, errp, ret);
		DZ1_STREAM_WRITE2(dst, cnt, ed, errp, ret);
		if ((*errp = src->travel(src, _Dz1MfcLanManPathList_write, (void *)&arg)).code) ERR_OUT_RET(errp, -1);
		else ret += arg.ret;
	}
	return ret;
}

ssize_t Dz1MfcLanManPathList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1MfcLanManPathList *dst = (Dz1MfcLanManPathList *)_dst;
	if (src == NULL || dst == NULL) ERR_SET_RET(errp, EINVAL, -1);
	else
	{
		u32_t v32 = 0;
		u16_t cnt, i;
		size_t my_sz = sizeof(TCHAR), sz = 0;
		Dz1MfcLanManPathEntry *node = NULL;
		DZ1_STREAM_READ4(&v32, src, ed, errp, ret); sz = (size_t)v32;
		if (my_sz != sz) ERR_SET_OUT_RET(errp, EPERM, -1);

		DZ1_STREAM_READ2(&cnt, src, ed, errp, ret);
		for (i = 0; errp->code == 0 && i < cnt; i++)
		{
			if ((node = Dz1MfcLanManPathEntry_gen(errp)) == NULL) ERR_OUT_RET(errp, -1);
			else
			{
				ssize_t status = 0;
				pthread_cleanup_push(Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
				if ((status = Dz1MfcLanManPathEntry_read(node, src, ed, param, errp)) < 0) { ERR_OUT(errp); ret = -1; }
				else if ((*errp = dst->add(dst, node)).code) { ERR_OUT(errp); ret = -1; }
				else
				{
					node = NULL;
					Dz1Error_set(errp, 0);
					ret += status;
				}
				pthread_cleanup_pop(1); // (Dz1MfcLanManPathEntry_delAndSetNull, (void *)&node);
			}
		}
	}
	return ret;
}
// Dz1MfcLanManPathList Stream Read/Write
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MfcLanManPathList Convert Utility
Dz1Error Dz1MfcLanManPathList_toStream(Dz1MfcLanManPathList *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t sz = 0;
		if ((sz = Dz1MfcLanManPathList_write(dst, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1MfcLanManPathList *Dz1MfcLanManPathList_fromStream(Dz1Stream *src, Dz1IOStreamEndian ed, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcLanManPathList *ret = Dz1MfcLanManPathList_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);
		if ((sz = Dz1MfcLanManPathList_read(ret, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MfcLanManPathList_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// Dz1MfcLanManPathList Convert Utility
////////////////////////////////////////////////////////////////////////////////

static Dz1Error _fix_full_path(Dz1MfcFolderTreeNode *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst->full_path == NULL || dst->full_path[0] == 0)
	{
		Dz1MfcFolderTreeNode *parent = dst->parent;
		if (parent == NULL)
		{	// 내가 Root
			if ((dst->full_path = Dz1Str_dup(dst->name, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		// 아니면
		else if ((*errp = _fix_full_path(parent)).code) ERR_OUT(errp);
		else
		{
			TCHAR path[4096];
			if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, path), parent->full_path, dst->name)).code) ERR_OUT(errp);
			else if ((dst->full_path = Dz1Str_dup(path, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error _add_child(Dz1MfcFolderTreeChilds *dst, Dz1DirEntry *src, Dz1MfcFolderTreeNode *parent)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcFolderTreeNode *node = Dz1MfcFolderTreeNode_new(src->name, src->date, parent, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1MfcFolderTreeChilds *_get_childs(Dz1Str path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFolderTreeChilds *ret = Dz1MfcFolderTreeChilds_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1DirCatalog *cat = NULL;
		pthread_cleanup_push(Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);
		if ((cat = Dz1DirCatalog_newSubDir(path, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			Dz1DirEntry *e = NULL;
			pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&cat);
			for (i = 0; errp->code == 0 && i < cat->valid; i++)
			{
				if ((*errp = _add_child(ret, &cat->entries[i], NULL)).code) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&cat);
		}
		pthread_cleanup_pop(errp->code); // (Dz1MfcFolderTreeChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

typedef struct CollectNotExistNodeArg
{
	Dz1MfcFolderTreeRefChilds	*result;
	Dz1MfcFolderTreeChilds		*base;
} CollectNotExistNodeArg;

static Dz1Error _collect_not_exist_node(void *ptr, Dz1MfcFolderTreeNode *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	CollectNotExistNodeArg *arg = (CollectNotExistNodeArg *)ptr;
	Dz1MfcFolderTreeChilds *base = arg->base;
	if (base->find(base, p) == NULL)
	{
		if ((*errp = arg->result->add(arg->result, p)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1MfcFolderTreeRefChilds *_collect_not_exist(Dz1MfcFolderTreeChilds *base, Dz1MfcFolderTreeChilds *modified, Dz1Error *errp)
{
	Dz1MfcFolderTreeRefChilds *ret = Dz1MfcFolderTreeRefChilds_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		CollectNotExistNodeArg arg = { ret, base };
		pthread_cleanup_push(Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);
		modified->travel(modified, _collect_not_exist_node, (void *)&arg);
		pthread_cleanup_pop(1); // (Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _remove_disappeared(Dz1MfcFolderTreeChilds *base, Dz1MfcFolderTreeChilds *modified)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcFolderTreeRefChilds *disappeared = _collect_not_exist(modified, base, errp);
	if (disappeared == NULL) ERR_OUT(errp);
	else
	{
		u32_t cnt = 0;
		Dz1MfcFolderTreeNode **arr = NULL;
		pthread_cleanup_push(Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&disappeared);

		if (disappeared->count(disappeared) == 0) { }
		else if ((arr = disappeared->get_array(disappeared, &cnt, errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			Dz1MfcFolderTreeNode *node = NULL;
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);

			for (i = 0; i < cnt; i++)
			{
				if (arr[i] != NULL && (node = base->extract(base, arr[i])) != NULL)
				{
					pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
					disappeared->remove(disappeared, node);
					pthread_cleanup_pop(1); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
				}
				arr[i] = NULL;
			}
			pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
		}
		pthread_cleanup_pop(1); // (Dz1MfcFolderTreeRefChilds_delAndSetNull, (void *)&disappeared);
	}
	return err;
}

typedef struct AppendAppearedNodeArg
{
	Dz1MfcFolderTreeChilds *dst;
	Dz1MfcFolderTreeNode *owner;
} AppendAppearedNodeArg;

static Dz1Error _append_appeared_node(void *ptr, Dz1MfcFolderTreeNode *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	AppendAppearedNodeArg *arg = (AppendAppearedNodeArg *)ptr;	
	if (arg->dst->find(arg->dst, p) == NULL)
	{
		Dz1MfcFolderTreeNode *node = Dz1MfcFolderTreeNode_new(p->name, p->stamp, arg->owner, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
			if ((*errp = arg->dst->add(arg->dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

static Dz1Error _append_appeared(Dz1MfcFolderTreeChilds *base, Dz1MfcFolderTreeChilds *modified, Dz1MfcFolderTreeNode *owner)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	AppendAppearedNodeArg arg = { base, owner };
	if ((*errp = modified->travel(modified, _append_appeared_node, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error Dz1MfcFolderTreeNode_syncChilds(Dz1MfcFolderTreeNode *dst)
{	// 주어진 폴더의 하위 목록을 갱신한다.
	DZ1_ERROR_SAFE_VAR(errp, err);
	time_t dir_stamp = 0;
	if ((*errp = _fix_full_path(dst)).code) ERR_OUT(errp);
	else if ((dir_stamp = Dz1Dir_time(dst->full_path, NULL)) == -1 || dir_stamp != dst->stamp)
	{	// 나의 마지막 변경 시간이 바뀌었다
		Dz1MfcFolderTreeChilds *real_childs = _get_childs(dst->full_path, errp);
		Dz1MfcFolderTreeChilds *dst_childs = dst->childs;
		if ((*errp = _remove_disappeared(dst_childs, real_childs)).code) ERR_OUT(errp);
		else if ((*errp = _append_appeared(dst_childs, real_childs, dst)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
// Drive Root Node 삽입, 하위 폴더 등록
static Dz1Error _add_child_of_drive(Dz1MfcFolderTreeChilds *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t done = FALSE;
	Dz1MfcFolderTreeNode *node = NULL;

	TCHAR names[256][4];
	DWORD len = 0, i;
	memset(names, 0, sizeof(TCHAR) * 256 * 4);
	len = GetLogicalDriveStrings(4096, (TCHAR *)names);
	len /= 4;

	for (i = 0; i < len && done == FALSE; i++)
	{
		Dz1Thread_printf(Dz1T("@@@ Add Root Node = ")); Dz1Str_dump(names[i], 0);
		if ((node = Dz1MfcFolderTreeNode_new(names[i], 0, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
			if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				Dz1MfcFolderTreeNode_syncChilds(node);
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

// 공유 폴더 Root Node 삽입
static Dz1Error _add_child_of_shares(Dz1MfcFolderTreeChilds *dst, Dz1MfcLanManPathList *lan_man_hosts)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (lan_man_hosts != NULL)
	{
		u32_t cnt = 0;
		Dz1MfcLanManPathEntry **arr = lan_man_hosts->get_array(lan_man_hosts, &cnt, errp);
		if (arr != NULL)
		{
			u32_t i;
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
			for (i = 0; i < cnt; i++)
			{
				if (Dz1Dir_isExist(arr[i]->name) == TRUE)
				{
					Dz1MfcFolderTreeNode *node = NULL;
					if ((node = Dz1MfcFolderTreeNode_new(arr[i]->name, 0, NULL, errp)) == NULL) ERR_OUT(errp);
					else
					{
						pthread_cleanup_push(Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
						if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
						else
						{
							Dz1MfcFolderTreeNode_syncChilds(node);
							node = NULL;
							Dz1Error_set(errp, 0);
						}
						pthread_cleanup_pop(1); // (Dz1MfcFolderTreeNode_delAndSetNull, (void *)&node);
					}
				}
			}
			pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
		}
	}
	return err;
}

Dz1MfcFolderTree *Dz1MfcFolderTree_generate(Dz1MfcLanManPathList *lm_path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFolderTree *ret = Dz1MfcFolderTree_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcFolderTree_delAndSetNull, (void *)&ret);
		if ((*errp = _add_child_of_drive(ret->hdd_roots)).code) ERR_OUT(errp);
		else if ((*errp = _add_child_of_shares(ret->share_roots, lm_path)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MfcFolderTree_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1MfcProgressInfo_setText(Dz1MfcProgressInfo *dst, Dz1Str text)
{
	if (dst != NULL)
	{
		Dz1STRNCPY(dst->text, text, 255); dst->text[255] = 0;
		dst->text_changed = TRUE;
	}
}

void Dz1MfcProgressInfo_setPos(Dz1MfcProgressInfo *dst, u64_t pos)
{
	if (dst != NULL) dst->curr = pos;
}

void Dz1MfcProgressInfo_addPos(Dz1MfcProgressInfo *dst, u64_t v)
{
	if (dst != NULL)
	{
		dst->curr += v;
//		Dz1Thread_printf(Dz1T("=== ") DZ1_FMT64U_A "/" DZ1_FMT64U_A "\n", dst->curr, dst->total);
	}
}

void Dz1MfcProgressInfo_subPos(Dz1MfcProgressInfo *dst, u64_t v)
{
	if (dst != NULL)
	{
		if (dst->curr > v) dst->curr -= v;
		else dst->curr = 0;
	}
}

void Dz1MfcProgressInfo_incPos(Dz1MfcProgressInfo *dst)
{
	if (dst != NULL) dst->curr++;
}

void Dz1MfcProgressInfo_decPos(Dz1MfcProgressInfo *dst)
{
	if (dst != NULL)
	{
		if (dst->curr > 0) dst->curr--;
	}
}

void Dz1MfcProgressInfo_setTotal(Dz1MfcProgressInfo *dst, u64_t total)
{
	if (dst != NULL) dst->total = total;
}

void Dz1MfcProgressInfo_addTotal(Dz1MfcProgressInfo *dst, u64_t v)
{
	if (dst != NULL)
	{
		if (dst->total == (u64_t)-1) dst->total = v;
		else dst->total += v;
	}
}

void Dz1MfcProgressInfo_subTotal(Dz1MfcProgressInfo *dst, u64_t v)
{
	if (dst != NULL && dst->total != (u64_t)-1 && dst->total > 0)
	{
		if (dst->total > v) dst->total -= v;
		else dst->total = 0;
	}
}

void Dz1MfcProgressInfo_incTotal(Dz1MfcProgressInfo *dst)
{
	if (dst != NULL)
	{
		if (dst->total == -1) dst->total = 1;
		else dst->total++;
	}
}

void Dz1MfcProgressInfo_decTotal(Dz1MfcProgressInfo *dst)
{
	if (dst != NULL && dst->total != (u64_t)-1 && dst->total > 0) dst->total--;
}

static Dz1Error Dz1MfcProgInfo_append_argv(Dz1MfcProgInfoArgList *dst, u32_t idx, Dz1Str str)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1MfcProgInfoArgEntry *node = Dz1MfcProgInfoArgEntry_new(idx, str, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1MfcProgInfoArgEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

#ifndef UNICODE
static char **CommandLineToArgvA(char *src, int *ret_argc)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	str_t *ret = NULL, temp = NULL;
	if (Dz1Str_isVoid(src)) ERR_SET_OUT(errp, EINVAL);
	else if ((temp = Dz1StrA_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *buf = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);

		if ((buf = Dz1Calloc(sizeof(char), strlen(temp) + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			str_t temp_argv[127] = { NULL, };
			int idx = 0;

			bool_t cotate = FALSE;
			char *sp = temp, *dp = buf;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
			while(errp->code == 0 && *sp)
			{
				if (cotate) ERR_SET_OUT(errp, EINVAL);
				else switch(*sp)
				{
				case Dz1T('\"'):	// double cotate string
					cotate = TRUE;
					sp++;											// skip '"'
					while(*sp && *sp != Dz1T('\"')) *dp++ = *sp++;	// copy until '"'
					if (*sp && *sp == Dz1T('\"')) { sp++; cotate = FALSE; }
					break;
				case Dz1T('\''):	// single cotate string
					cotate = TRUE;
					sp++;											// skip '\''
					while(*sp && *sp != Dz1T('\'')) *dp++ = *sp++;	// copy until '\''
					if (*sp && *sp == Dz1T('\'')) { sp++; cotate = FALSE; }
					break;
				default:
					if (Dz1ISSPACE(*sp))
					{
						*dp++ = 0;
						while(*sp && Dz1ISSPACE(*sp)) sp++;				// skip whitespace
						if ((temp_argv[idx] = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp); else { idx++; dp = buf; }
					}
					else *dp++ = *sp++;
					break;
				}
			}

			if (errp->code == 0 && dp > buf)
			{	// 마지막 구문 추가
				*dp = 0;
				if ((temp_argv[idx] = Dz1StrA_dup(buf, errp)) == NULL) ERR_OUT(errp);
				else { idx++; dp = buf; }
			}

			if (errp->code == 0)
			{
				if ((ret = (str_t *)Dz1Calloc(sizeof(str_t), idx, errp)) == NULL) ERR_OUT(errp);
				else
				{
					int i;
					for (i = 0; i < idx; i++)
					{
						ret[i] = temp_argv[i];
						temp_argv[i] = NULL;
					}

					if (ret_argc != NULL) *ret_argc = idx;
				}

			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
	}
	return ret;
}

static void CascadeFree(char **argv, int argc)
{
	if (argv != NULL)
	{
		int i;
		for (i = 0; i < argc; i++)
		{
			if (argv[i] != NULL) 
			{
				Dz1Free(argv[i]); 
				argv[i] = NULL;
			}
		}
		Dz1Free(argv);
	}
}
#endif

Dz1MfcProgInfo *Dz1MfcProgInfo_generate(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1MfcProgInfo *ret = NULL;
	
	int argc = 0;
	TCHAR *cmd_str = GetCommandLine();
#ifdef UNICODE
	wchar_t **argv = CommandLineToArgvW(cmd_str, &argc);
#else
	char **argv = CommandLineToArgvA(cmd_str, &argc);
#endif
	if (argv == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		Dz1Thread_printf(Dz1T("CMD = ")); Dz1Str_dump(cmd_str, 0);
		if ((ret = Dz1MfcProgInfo_new(cmd_str, argv[0], NULL, NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			TCHAR long_str[4096], short_str[1024];
			pthread_cleanup_push(Dz1MfcProgInfo_delAndSetNull, (void *)&ret);

			if		((*errp			= Dz1FileName_splitPathName(long_str, short_str, ret->path_name_ext)).code) ERR_OUT(errp);
			else if ((ret->path		= Dz1Str_dup(long_str, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->name_ext = Dz1Str_dup(short_str, errp)) == NULL) ERR_OUT(errp);
			else if ((*errp			= Dz1FileName_splitNameExt(long_str, short_str, ret->name_ext)).code) ERR_OUT(errp);
			else if ((ret->name		= Dz1Str_dup(long_str, errp)) == NULL) ERR_OUT(errp);
			else if ((ret->ext		= Dz1Str_dup(short_str, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				if (argc > 1)
				{
					int i;
					u32_t idx;
					for (i = 1, idx = 0; i < argc; i++, idx++)
						Dz1MfcProgInfo_append_argv(ret->args, idx, argv[i]);
				}
			}
			pthread_cleanup_pop(errp->code); // (Dz1MfcProgInfo_delAndSetNull, (void *)&ret);
		}
#ifdef UNICODE
		LocalFree(argv);
#else
		CascadeFree(argv, argc);
#endif
	}
	return ret;
}

Dz1Str Dz1MfcProgInfo_getArgv(Dz1MfcProgInfo *info, u32_t idx, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str ret = NULL;
	if (info == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (idx >= info->args->count(info->args)) Dz1Error_set(errp, ENOENT);
	else
	{
		Dz1MfcProgInfoArgEntry key = { idx }, *node = info->args->find(info->args, &key);
		if (node != NULL) ret = node->str;
		else ERR_SET_OUT(errp, EFAULT);
	}
	return ret;
}

void Dz1MfcProgressInfo_dump(Dz1MfcProgressInfo *p, int tab)
{
	if (p == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(DZ1_FMT64U Dz1T("/") DZ1_FMT64U Dz1T("\n"), p->curr, p->total);
}

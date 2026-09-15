#include <dz1_str.h>
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>

#include "dz1_vfs_def.h"

Dz1VfsFile *Dz1VfsFile_new(
			u32_t idx,
			Dz1MetaTagTargetType body_type,
			u32_t body_idx,
			Dz1MetaTagData *tags, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsFile *__internal_ret = (Dz1VfsFile *)Dz1Calloc(sizeof(Dz1VfsFile), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsFile_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->idx = idx;
		__internal_ret->body_type = body_type;
		__internal_ret->body_idx = body_idx;
		__internal_ret->tags = tags;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsFile_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsFile_del(Dz1VfsFile *p)
{
	if (p == NULL) return;
	if (p->tags) Dz1MetaTagData_del(p->tags);
	Dz1Free(p);
}

void Dz1VfsFile_dump(Dz1VfsFile *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	Dz1Thread_tprintf(tab, "body_type = %s(%d)\n", Dz1MetaTagTargetTypeStr(p->body_type), p->body_type);

	Dz1Thread_tprintf(tab, "body_idx = "); Dz1u32_dump(&p->body_idx, tab);

	if (p->tags == NULL) Dz1Thread_tprintf(tab, "tags = NULL\n");
	else { Dz1Thread_tprintf(tab, "tags = "); Dz1MetaTagData_dump(p->tags, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsFile_cmp(Dz1VfsFile *a, Dz1VfsFile *b)
{
	int ret = 0;
	if ((ret = (int)((a->idx) - (b->idx))) != 0) return ret;
	else return ret;
}

Dz1VfsChildNode *Dz1VfsChildNode_new(Dz1Asn1UTF8Str *name, u32_t idx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsChildNode *__internal_ret = (Dz1VfsChildNode *)Dz1Calloc(sizeof(Dz1VfsChildNode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsChildNode_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->name = name;
		__internal_ret->idx = idx;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsChildNode_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsChildNode_del(Dz1VfsChildNode *p)
{
	if (p == NULL) return;
	if (p->name) Dz1Asn1UTF8Str_del(p->name);
	Dz1Free(p);
}

void Dz1VfsChildNode_dump(Dz1VfsChildNode *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->name == NULL) Dz1Thread_tprintf(tab, "name = NULL\n");
	else { Dz1Thread_tprintf(tab, "name = "); Dz1Asn1UTF8Str_dump(p->name, tab); }

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsChildNode_cmp(Dz1VfsChildNode *a, Dz1VfsChildNode *b)
{
	int ret = 0;
	if ((ret = Dz1Asn1UTF8Str_cmp(a->name, b->name)) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1VfsChildList_add(Dz1VfsChildList *p, Dz1VfsChildNode *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1VfsChildList_remove(Dz1VfsChildList *p, Dz1VfsChildNode *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1VfsChildNode *Dz1VfsChildList_extract(Dz1VfsChildList *p, Dz1VfsChildNode *key)
{
	return (Dz1VfsChildNode *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error Dz1VfsChildList_travelForward(Dz1VfsChildList *p, Dz1Error (*func)(void *ptr, Dz1VfsChildNode *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1VfsChildList_travelBackward(Dz1VfsChildList *p, Dz1Error (*func)(void *ptr, Dz1VfsChildNode *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1VfsChildNode *Dz1VfsChildList_find(Dz1VfsChildList *p, Dz1VfsChildNode *key)
{
	return (Dz1VfsChildNode *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1VfsChildList_count(Dz1VfsChildList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1VfsChildList_dump(Dz1VfsChildNode *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1VfsChildNode_dump(p, tab);
	}
}

Dz1VfsChildList *Dz1VfsChildList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsChildList *ret = (Dz1VfsChildList *)Dz1Calloc(sizeof(Dz1VfsChildList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsChildList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1VfsChildNode_cmp,
				(Dz1DelFunc)Dz1VfsChildNode_del,
				(Dz1DumpFunc)_Dz1VfsChildList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1VfsChildList_add;
			ret->remove = Dz1VfsChildList_remove;
			ret->extract = Dz1VfsChildList_extract;
			ret->travel = Dz1VfsChildList_travelForward;
			ret->travelForward = Dz1VfsChildList_travelForward;
			ret->travelBackward = Dz1VfsChildList_travelBackward;
			ret->find = Dz1VfsChildList_find;
			ret->count = Dz1VfsChildList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsChildList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsChildList_del(Dz1VfsChildList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1VfsChildList_dump(Dz1VfsChildList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1VfsDir *Dz1VfsDir_new(
			u32_t idx,
			u32_t parent_idx,
			Dz1MetaTagData *tags, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsDir *__internal_ret = (Dz1VfsDir *)Dz1Calloc(sizeof(Dz1VfsDir), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->dirs = Dz1VfsChildList_new(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->files = Dz1VfsChildList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->idx = idx;
			__internal_ret->parent_idx = parent_idx;
			__internal_ret->tags = tags;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsDir_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsDir_del(Dz1VfsDir *p)
{
	if (p == NULL) return;
	if (p->tags) Dz1MetaTagData_del(p->tags);
	if (p->dirs) Dz1VfsChildList_del(p->dirs);
	if (p->files) Dz1VfsChildList_del(p->files);
	Dz1Free(p);
}

void Dz1VfsDir_dump(Dz1VfsDir *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	Dz1Thread_tprintf(tab, "parent_idx = "); Dz1u32_dump(&p->parent_idx, tab);

	if (p->tags == NULL) Dz1Thread_tprintf(tab, "tags = NULL\n");
	else { Dz1Thread_tprintf(tab, "tags = "); Dz1MetaTagData_dump(p->tags, tab); }

	if (p->dirs == NULL) Dz1Thread_tprintf(tab, "dirs = NULL\n");
	else { Dz1Thread_tprintf(tab, "dirs = "); Dz1VfsChildList_dump(p->dirs, tab); }

	if (p->files == NULL) Dz1Thread_tprintf(tab, "files = NULL\n");
	else { Dz1Thread_tprintf(tab, "files = "); Dz1VfsChildList_dump(p->files, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsDir_cmp(Dz1VfsDir *a, Dz1VfsDir *b)
{
	int ret = 0;
	if ((ret = (int)((a->idx) - (b->idx))) != 0) return ret;
	else return ret;
}

Dz1VfsHandleFileInfo *Dz1VfsHandleFileInfo_new(
			u32_t handle_id,
			bool_t read,
			bool_t write,
			bool_t seek,
			bool_t tagChanged,
			bool_t dataChanged,
			Dz1StoragePos *pos, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleFileInfo *__internal_ret = (Dz1VfsHandleFileInfo *)Dz1Calloc(sizeof(Dz1VfsHandleFileInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsHandleFileInfo_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->handle_id = handle_id;
		__internal_ret->read = read;
		__internal_ret->write = write;
		__internal_ret->seek = seek;
		__internal_ret->tagChanged = tagChanged;
		__internal_ret->dataChanged = dataChanged;
		__internal_ret->pos = pos;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleFileInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsHandleFileInfo_del(Dz1VfsHandleFileInfo *p)
{
	if (p == NULL) return;
	if (p->pos) Dz1StoragePos_del(p->pos);
	Dz1Free(p);
}

void Dz1VfsHandleFileInfo_dump(Dz1VfsHandleFileInfo *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "handle_id = "); Dz1u32_dump(&p->handle_id, tab);

	Dz1Thread_tprintf(tab, "read = "); Dz1Bool_dump(&p->read, tab);

	Dz1Thread_tprintf(tab, "write = "); Dz1Bool_dump(&p->write, tab);

	Dz1Thread_tprintf(tab, "seek = "); Dz1Bool_dump(&p->seek, tab);

	Dz1Thread_tprintf(tab, "tagChanged = "); Dz1Bool_dump(&p->tagChanged, tab);

	Dz1Thread_tprintf(tab, "dataChanged = "); Dz1Bool_dump(&p->dataChanged, tab);

	if (p->pos == NULL) Dz1Thread_tprintf(tab, "pos = NULL\n");
	else { Dz1Thread_tprintf(tab, "pos = "); Dz1StoragePos_dump(p->pos, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsHandleFileInfo_cmp(Dz1VfsHandleFileInfo *a, Dz1VfsHandleFileInfo *b)
{
	int ret = 0;
	if ((ret = (int)((a->handle_id) - (b->handle_id))) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1VfsHandleFileInfoList_add(Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1VfsHandleFileInfoList_remove(Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1VfsHandleFileInfo *Dz1VfsHandleFileInfoList_extract(Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key)
{
	return (Dz1VfsHandleFileInfo *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error Dz1VfsHandleFileInfoList_travelForward(Dz1VfsHandleFileInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileInfo *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1VfsHandleFileInfoList_travelBackward(Dz1VfsHandleFileInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileInfo *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1VfsHandleFileInfo *Dz1VfsHandleFileInfoList_find(Dz1VfsHandleFileInfoList *p, Dz1VfsHandleFileInfo *key)
{
	return (Dz1VfsHandleFileInfo *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1VfsHandleFileInfoList_count(Dz1VfsHandleFileInfoList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1VfsHandleFileInfoList_dump(Dz1VfsHandleFileInfo *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1VfsHandleFileInfo_dump(p, tab);
	}
}

Dz1VfsHandleFileInfoList *Dz1VfsHandleFileInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleFileInfoList *ret = (Dz1VfsHandleFileInfoList *)Dz1Calloc(sizeof(Dz1VfsHandleFileInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleFileInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1VfsHandleFileInfo_cmp,
				(Dz1DelFunc)Dz1VfsHandleFileInfo_del,
				(Dz1DumpFunc)_Dz1VfsHandleFileInfoList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1VfsHandleFileInfoList_add;
			ret->remove = Dz1VfsHandleFileInfoList_remove;
			ret->extract = Dz1VfsHandleFileInfoList_extract;
			ret->travel = Dz1VfsHandleFileInfoList_travelForward;
			ret->travelForward = Dz1VfsHandleFileInfoList_travelForward;
			ret->travelBackward = Dz1VfsHandleFileInfoList_travelBackward;
			ret->find = Dz1VfsHandleFileInfoList_find;
			ret->count = Dz1VfsHandleFileInfoList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleFileInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsHandleFileInfoList_del(Dz1VfsHandleFileInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1VfsHandleFileInfoList_dump(Dz1VfsHandleFileInfoList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1VfsHandleFileEntry *Dz1VfsHandleFileEntry_new(
			u32_t idx,
			Dz1Sync *sync,
			Dz1VfsFile *source, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleFileEntry *__internal_ret = (Dz1VfsHandleFileEntry *)Dz1Calloc(sizeof(Dz1VfsHandleFileEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsHandleFileEntry_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->handles = Dz1VfsHandleFileInfoList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->idx = idx;
			__internal_ret->sync = sync;
			__internal_ret->source = source;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleFileEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsHandleFileEntry_del(Dz1VfsHandleFileEntry *p)
{
	if (p == NULL) return;
	if (p->sync) Dz1Sync_del(p->sync);
	if (p->source) Dz1VfsFile_del(p->source);
	if (p->handles) Dz1VfsHandleFileInfoList_del(p->handles);
	Dz1Free(p);
}

void Dz1VfsHandleFileEntry_dump(Dz1VfsHandleFileEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	if (p->sync == NULL) Dz1Thread_tprintf(tab, "sync = NULL\n");
	else { Dz1Thread_tprintf(tab, "sync = %p\n", p->sync); }

	if (p->source == NULL) Dz1Thread_tprintf(tab, "source = NULL\n");
	else { Dz1Thread_tprintf(tab, "source = "); Dz1VfsFile_dump(p->source, tab); }

	if (p->handles == NULL) Dz1Thread_tprintf(tab, "handles = NULL\n");
	else { Dz1Thread_tprintf(tab, "handles = "); Dz1VfsHandleFileInfoList_dump(p->handles, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsHandleFileEntry_cmp(Dz1VfsHandleFileEntry *a, Dz1VfsHandleFileEntry *b)
{
	int ret = 0;
	if ((ret = (int)((a->idx) - (b->idx))) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1VfsHandleFileList_add(Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1VfsHandleFileList_remove(Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1VfsHandleFileEntry *Dz1VfsHandleFileList_extract(Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key)
{
	return (Dz1VfsHandleFileEntry *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error Dz1VfsHandleFileList_travelForward(Dz1VfsHandleFileList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1VfsHandleFileList_travelBackward(Dz1VfsHandleFileList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleFileEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1VfsHandleFileEntry *Dz1VfsHandleFileList_find(Dz1VfsHandleFileList *p, Dz1VfsHandleFileEntry *key)
{
	return (Dz1VfsHandleFileEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1VfsHandleFileList_count(Dz1VfsHandleFileList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1VfsHandleFileList_dump(Dz1VfsHandleFileEntry *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1VfsHandleFileEntry_dump(p, tab);
	}
}

Dz1VfsHandleFileList *Dz1VfsHandleFileList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleFileList *ret = (Dz1VfsHandleFileList *)Dz1Calloc(sizeof(Dz1VfsHandleFileList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleFileList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1VfsHandleFileEntry_cmp,
				(Dz1DelFunc)Dz1VfsHandleFileEntry_del,
				(Dz1DumpFunc)_Dz1VfsHandleFileList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1VfsHandleFileList_add;
			ret->remove = Dz1VfsHandleFileList_remove;
			ret->extract = Dz1VfsHandleFileList_extract;
			ret->travel = Dz1VfsHandleFileList_travelForward;
			ret->travelForward = Dz1VfsHandleFileList_travelForward;
			ret->travelBackward = Dz1VfsHandleFileList_travelBackward;
			ret->find = Dz1VfsHandleFileList_find;
			ret->count = Dz1VfsHandleFileList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleFileList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsHandleFileList_del(Dz1VfsHandleFileList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1VfsHandleFileList_dump(Dz1VfsHandleFileList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1VfsHandleDir *Dz1VfsHandleDir_new(
			u32_t handle_id,
			bool_t tagChanged,
			bool_t childChanged,
			bool_t fileChanged, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleDir *__internal_ret = (Dz1VfsHandleDir *)Dz1Calloc(sizeof(Dz1VfsHandleDir), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDir_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->handle_id = handle_id;
		__internal_ret->tagChanged = tagChanged;
		__internal_ret->childChanged = childChanged;
		__internal_ret->fileChanged = fileChanged;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleDir_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsHandleDir_del(Dz1VfsHandleDir *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1VfsHandleDir_dump(Dz1VfsHandleDir *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "handle_id = "); Dz1u32_dump(&p->handle_id, tab);

	Dz1Thread_tprintf(tab, "tagChanged = "); Dz1Bool_dump(&p->tagChanged, tab);

	Dz1Thread_tprintf(tab, "childChanged = "); Dz1Bool_dump(&p->childChanged, tab);

	Dz1Thread_tprintf(tab, "fileChanged = "); Dz1Bool_dump(&p->fileChanged, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsHandleDir_cmp(Dz1VfsHandleDir *a, Dz1VfsHandleDir *b)
{
	int ret = 0;
	if ((ret = (int)((a->handle_id) - (b->handle_id))) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1VfsHandleDirInfoList_add(Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1VfsHandleDirInfoList_remove(Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1VfsHandleDir *Dz1VfsHandleDirInfoList_extract(Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key)
{
	return (Dz1VfsHandleDir *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error Dz1VfsHandleDirInfoList_travelForward(Dz1VfsHandleDirInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDir *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1VfsHandleDirInfoList_travelBackward(Dz1VfsHandleDirInfoList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDir *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1VfsHandleDir *Dz1VfsHandleDirInfoList_find(Dz1VfsHandleDirInfoList *p, Dz1VfsHandleDir *key)
{
	return (Dz1VfsHandleDir *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1VfsHandleDirInfoList_count(Dz1VfsHandleDirInfoList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1VfsHandleDirInfoList_dump(Dz1VfsHandleDir *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1VfsHandleDir_dump(p, tab);
	}
}

Dz1VfsHandleDirInfoList *Dz1VfsHandleDirInfoList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleDirInfoList *ret = (Dz1VfsHandleDirInfoList *)Dz1Calloc(sizeof(Dz1VfsHandleDirInfoList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDirInfoList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1VfsHandleDir_cmp,
				(Dz1DelFunc)Dz1VfsHandleDir_del,
				(Dz1DumpFunc)_Dz1VfsHandleDirInfoList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1VfsHandleDirInfoList_add;
			ret->remove = Dz1VfsHandleDirInfoList_remove;
			ret->extract = Dz1VfsHandleDirInfoList_extract;
			ret->travel = Dz1VfsHandleDirInfoList_travelForward;
			ret->travelForward = Dz1VfsHandleDirInfoList_travelForward;
			ret->travelBackward = Dz1VfsHandleDirInfoList_travelBackward;
			ret->find = Dz1VfsHandleDirInfoList_find;
			ret->count = Dz1VfsHandleDirInfoList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleDirInfoList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsHandleDirInfoList_del(Dz1VfsHandleDirInfoList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1VfsHandleDirInfoList_dump(Dz1VfsHandleDirInfoList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1VfsHandleDirEntry *Dz1VfsHandleDirEntry_new(
			u32_t idx,
			Dz1Sync *sync,
			Dz1VfsDir *source, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleDirEntry *__internal_ret = (Dz1VfsHandleDirEntry *)Dz1Calloc(sizeof(Dz1VfsHandleDirEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDirEntry_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->handles = Dz1VfsHandleDirInfoList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->idx = idx;
			__internal_ret->sync = sync;
			__internal_ret->source = source;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleDirEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsHandleDirEntry_del(Dz1VfsHandleDirEntry *p)
{
	if (p == NULL) return;
	if (p->sync) Dz1Sync_del(p->sync);
	if (p->source) Dz1VfsDir_del(p->source);
	if (p->handles) Dz1VfsHandleDirInfoList_del(p->handles);
	Dz1Free(p);
}

void Dz1VfsHandleDirEntry_dump(Dz1VfsHandleDirEntry *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	if (p->source == NULL) Dz1Thread_tprintf(tab, "source = NULL\n");
	else { Dz1Thread_tprintf(tab, "source = "); Dz1VfsDir_dump(p->source, tab); }

	if (p->handles == NULL) Dz1Thread_tprintf(tab, "handles = NULL\n");
	else { Dz1Thread_tprintf(tab, "handles = "); Dz1VfsHandleDirInfoList_dump(p->handles, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}

int Dz1VfsHandleDirEntry_cmp(Dz1VfsHandleDirEntry *a, Dz1VfsHandleDirEntry *b)
{
	int ret = 0;
	if ((ret = (int)((a->idx) - (b->idx))) != 0) return ret;
	else return ret;
}

static Dz1Error Dz1VfsHandleDirList_add(Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static void Dz1VfsHandleDirList_remove(Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key)
{
	Dz1AATree_remove(p->storage, key);
}

static Dz1VfsHandleDirEntry *Dz1VfsHandleDirList_extract(Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key)
{
	return (Dz1VfsHandleDirEntry *)Dz1AATree_extract(p->storage, key);
}

static Dz1Error Dz1VfsHandleDirList_travelForward(Dz1VfsHandleDirList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDirEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1VfsHandleDirList_travelBackward(Dz1VfsHandleDirList *p, Dz1Error (*func)(void *ptr, Dz1VfsHandleDirEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1VfsHandleDirEntry *Dz1VfsHandleDirList_find(Dz1VfsHandleDirList *p, Dz1VfsHandleDirEntry *key)
{
	return (Dz1VfsHandleDirEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int Dz1VfsHandleDirList_count(Dz1VfsHandleDirList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

void _Dz1VfsHandleDirList_dump(Dz1VfsHandleDirEntry *p, int tab)
{
	if (p == NULL) Dz1Thread_tprintf(tab, "entry = NULL\n");
	else
	{
		Dz1Thread_tprintf(tab, "entry = ");
		Dz1VfsHandleDirEntry_dump(p, tab);
	}
}

Dz1VfsHandleDirList *Dz1VfsHandleDirList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleDirList *ret = (Dz1VfsHandleDirList *)Dz1Calloc(sizeof(Dz1VfsHandleDirList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDirList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1VfsHandleDirEntry_cmp,
				(Dz1DelFunc)Dz1VfsHandleDirEntry_del,
				(Dz1DumpFunc)_Dz1VfsHandleDirList_dump, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->add = Dz1VfsHandleDirList_add;
			ret->remove = Dz1VfsHandleDirList_remove;
			ret->extract = Dz1VfsHandleDirList_extract;
			ret->travel = Dz1VfsHandleDirList_travelForward;
			ret->travelForward = Dz1VfsHandleDirList_travelForward;
			ret->travelBackward = Dz1VfsHandleDirList_travelBackward;
			ret->find = Dz1VfsHandleDirList_find;
			ret->count = Dz1VfsHandleDirList_count;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleDirList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsHandleDirList_del(Dz1VfsHandleDirList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

void Dz1VfsHandleDirList_dump(Dz1VfsHandleDirList *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	if (p->storage)
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1AATree_dump(p->storage, tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

Dz1VfsHandleID *Dz1VfsHandleID_new(u32_t idx, u32_t handle, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsHandleID *__internal_ret = (Dz1VfsHandleID *)Dz1Calloc(sizeof(Dz1VfsHandleID), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsHandleID_delAndSetNull, (void *)&__internal_ret);

		__internal_ret->idx = idx;
		__internal_ret->handle = handle;
		ERR_CLEAR(errp);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsHandleID_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1VfsHandleID_del(Dz1VfsHandleID *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

void Dz1VfsHandleID_dump(Dz1VfsHandleID *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	Dz1Thread_tprintf(tab, "idx = "); Dz1u32_dump(&p->idx, tab);

	Dz1Thread_tprintf(tab, "handle = "); Dz1u32_dump(&p->handle, tab);

	Dz1Thread_tprintf(--tab, "}\n");
}

static struct Dz1VfsAccessPresentMap
{
	str_t str;
	Dz1VfsAccessPresent v;
} Dz1VfsAccessPresentMap[] =
{
	{ "dir", Dz1VfsAccessPresent_dir },
	{ "file", Dz1VfsAccessPresent_file },
	{ NULL, Dz1VfsAccessPresent_max }
};

str_t Dz1VfsAccessPresentStr(Dz1VfsAccessPresent v)
{
	struct Dz1VfsAccessPresentMap *i = NULL;
	for (i = Dz1VfsAccessPresentMap; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1VfsAccessPresent Dz1VfsAccessPresentFromStr(str_t str)
{
	struct Dz1VfsAccessPresentMap *i = NULL;
	for (i = Dz1VfsAccessPresentMap; i->str; i++)
		if (strcmp(i->str, str) == 0) return i->v;
	return Dz1VfsAccessPresent_max;
}

Dz1VfsAccessPresent *Dz1VfsAccessPresent_new(Dz1VfsAccessPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsAccessPresent *__internal_ret = (Dz1VfsAccessPresent *)Dz1Calloc(sizeof(Dz1VfsAccessPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
	}
	return __internal_ret;
}

void Dz1VfsAccessPresent_dump(Dz1VfsAccessPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf("NULL\n");
	else Dz1Thread_printf("%s\n", Dz1VfsAccessPresentStr(*v));
}

Dz1VfsAccess *Dz1VfsAccess_new(Dz1VfsAccessPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1VfsAccess *ret = (Dz1VfsAccess *)Dz1Calloc(sizeof(Dz1VfsAccess), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1VfsAccess_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
			case Dz1VfsAccessPresent_dir:
				ret->x.dir = (Dz1VfsHandleID *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1VfsAccessPresent_file:
				ret->x.file = (Dz1VfsHandleID *)ptr; // Pointer Construct Assign
				ERR_CLEAR(errp);
				break;
			case Dz1VfsAccessPresent_max:
				break;
			default:
				ERR_SET_OUT(errp, EINVAL);
				break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1VfsAccess_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1VfsAccess_del(Dz1VfsAccess *p)
{
	if (!p) return;
	switch(p->present)
	{
		case Dz1VfsAccessPresent_dir:
			if (p->x.dir) Dz1VfsHandleID_del(p->x.dir);
			break;
		case Dz1VfsAccessPresent_file:
			if (p->x.file) Dz1VfsHandleID_del(p->x.file);
			break;
		default:
			break;
	}
	Dz1Free(p);
}

void Dz1VfsAccess_dump(Dz1VfsAccess *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	switch(p->present)
	{
		case Dz1VfsAccessPresent_dir:
			if (p->x.dir == NULL) Dz1Thread_tprintf(tab, "dir = NULL\n");
			else { Dz1Thread_tprintf(tab, "dir = "); Dz1VfsHandleID_dump(p->x.dir, tab); } // Pointer Construct with DUMP API
			break;
		case Dz1VfsAccessPresent_file:
			if (p->x.file == NULL) Dz1Thread_tprintf(tab, "file = NULL\n");
			else { Dz1Thread_tprintf(tab, "file = "); Dz1VfsHandleID_dump(p->x.file, tab); } // Pointer Construct with DUMP API
			break;
		default:
			break;
	}
}

Dz1Vfs *Dz1Vfs_new(
			Dz1VfsAccess *root,
			Dz1StorageHandle *io, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Vfs *__internal_ret = (Dz1Vfs *)Dz1Calloc(sizeof(Dz1Vfs), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Vfs_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->dirHandles = Dz1VfsHandleDirList_new(errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->fileHandles = Dz1VfsHandleFileList_new(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->root = root;
			__internal_ret->io = io;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Vfs_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1Vfs_del(Dz1Vfs *p)
{
	if (p == NULL) return;
	if (p->root) Dz1VfsAccess_del(p->root);
	if (p->io) Dz1StorageHandle_del(p->io);
	if (p->dirHandles) Dz1VfsHandleDirList_del(p->dirHandles);
	if (p->fileHandles) Dz1VfsHandleFileList_del(p->fileHandles);
	Dz1Free(p);
}

void Dz1Vfs_dump(Dz1Vfs *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("{\n"); tab++;

	if (p->root == NULL) Dz1Thread_tprintf(tab, "root = NULL\n");
	else { Dz1Thread_tprintf(tab, "root."); Dz1VfsAccess_dump(p->root, tab); }

	if (p->io == NULL) Dz1Thread_tprintf(tab, "io = NULL\n");
	else { Dz1Thread_tprintf(tab, "io = "); Dz1StorageHandle_dump(p->io, tab); }

	if (p->dirHandles == NULL) Dz1Thread_tprintf(tab, "dirHandles = NULL\n");
	else { Dz1Thread_tprintf(tab, "dirHandles = "); Dz1VfsHandleDirList_dump(p->dirHandles, tab); }

	if (p->fileHandles == NULL) Dz1Thread_tprintf(tab, "fileHandles = NULL\n");
	else { Dz1Thread_tprintf(tab, "fileHandles = "); Dz1VfsHandleFileList_dump(p->fileHandles, tab); }

	Dz1Thread_tprintf(--tab, "}\n");
}


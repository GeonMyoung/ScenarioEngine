#include "dz1_storage.h"

#define DZ1_STORAGE_FILE_MAGIC		0x6A504154		// jPAT
#define DZ1_STORAGE_FILE_VERSION	0x00000001
static Dz1Error _save_header(Dz1Storage *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1StorageSuperFrag_save(p->fp, &p->hdr)).code) ERR_OUT(errp);

	return err;
}

static Dz1Error _load_old_header(Dz1Storage *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1StorageFrag frag = { 0, 0, 0, { 0, } };
	ssize_t status = 0, temp = 0;

	if ((*errp = Dz1StorageFrag_load(p->fp, 0, &frag)).code) ERR_OUT(errp);
	else
	{
		u8_t *cp = frag.data;
		size_t size = (size_t)frag.chunk_size;

		if ((status = _get4Byte(cp, size, &p->hdr.magic, errp)) < 0) { ERR_OUT(errp); return err; } else DZ1_CODEC_APPLY(cp, size, status, temp);

		if (p->hdr.magic != DZ1_STORAGE_FILE_MAGIC) { ERR_SET_OUT(errp, EINVAL); return err; }

		if ((status = _get4Byte(cp, size, &p->hdr.space_start, errp)) < 0) { ERR_OUT(errp); return err; } else DZ1_CODEC_APPLY(cp, size, status, temp);
	}
	return err;
}

static Dz1Error _load_header(Dz1Storage *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1StorageSuperFrag_load(p->fp, &p->hdr)).code) ERR_OUT(errp);
	else if (p->magic != p->hdr.magic)
	{
		if (p->hdr.magic == 0 && p->hdr.version == 0)
		{
			if ((*errp = _load_old_header(p)).code) ERR_OUT(errp);
			else
			{
				p->hdr.magic = p->magic;
				p->hdr.version = DZ1_STORAGE_FILE_VERSION;
				_save_header(p);
			}
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	return err;
}

static Dz1Error Dz1StorageA_create(str_t fn, Dz1Storage *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((ret->fp = Dz1FileStream_open(fn, "w+b", errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->hdr.magic = ret->magic;
		ret->hdr.version = DZ1_STORAGE_FILE_VERSION;
		ret->hdr.space_start = DZ1_STORAGE_FRAG_IDX_NONE;
		if ((*errp = _save_header(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

#ifndef UNIX_SYSTEM
static Dz1Error Dz1StorageW_create(wstr_t fn, Dz1Storage *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((ret->fp = Dz1FileStreamW_open(fn, L"w+b", errp)) == NULL) ERR_OUT(errp);
	else
	{
		ret->hdr.magic = ret->magic;
		ret->hdr.version = DZ1_STORAGE_FILE_VERSION;
		ret->hdr.space_start = DZ1_STORAGE_FRAG_IDX_NONE;
		if ((*errp = _save_header(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}
#endif

static long _get_file_size(FILE *fp)
{
	long curr = ftell(fp), ret = 0;
	fseek(fp, 0, SEEK_END);
	ret = ftell(fp);
	fseek(fp, curr, SEEK_SET);
	return ret;
}

Dz1StorageHandle *Dz1StorageA_new(str_t fn, u32_t magic, bool_t *is_created, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *ret = NULL;
	
	if (fn == NULL || fn[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Storage *)Dz1Calloc(sizeof(Dz1Storage), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t want_create = is_created == NULL ? FALSE : TRUE;
		bool_t _is_created, *is_crep = is_created ? is_created : &_is_created;

		pthread_cleanup_push(Dz1Storage_delAndSetNull, (void *)&ret);
		(*is_crep) = FALSE;
		ret->magic = magic;
		if ((ret->fp = Dz1FileStream_open(fn, "r+b", errp)) == NULL)
		{
			if (want_create == FALSE) { }
			else if ((*errp = Dz1StorageA_create(fn, ret)).code) ERR_OUT(errp);
			else
			{
				(*is_crep) = TRUE;
				Dz1Error_set(errp, 0);
			}
		}
		else if (_get_file_size(ret->fp) == 0)
		{
			fclose(ret->fp);
			ret->fp = NULL;
			Dz1FileA_delete(fn);
			if (want_create == FALSE) Dz1Error_set(errp, ENOENT);
			else if ((*errp = Dz1StorageA_create(fn, ret)).code) ERR_OUT(errp);
			else
			{
				(*is_created) = TRUE;
				Dz1Error_set(errp, 0);
			}
		}
		else if ((*errp = _load_header(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Storage_delAndSetNull, (void *)&ret);
	}
	return (Dz1StorageHandle *)ret;
}

#ifndef UNIX_SYSTEM
Dz1StorageHandle *Dz1StorageW_new(wstr_t fn, u32_t magic, bool_t *is_created, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *ret = NULL;
	
	if (fn == NULL || fn[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Storage *)Dz1Calloc(sizeof(Dz1Storage), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		bool_t want_create = is_created == NULL ? FALSE : TRUE;
		bool_t _is_created, *is_crep = is_created ? is_created : &_is_created;

		pthread_cleanup_push(Dz1Storage_delAndSetNull, (void *)&ret);
		(*is_crep) = FALSE;
		ret->magic = magic;
		if ((ret->fp = Dz1FileStreamW_open(fn, L"r+b", errp)) == NULL)
		{
			if (want_create == FALSE) { }
			else if ((*errp = Dz1StorageW_create(fn, ret)).code) ERR_OUT(errp);
			else
			{
				(*is_created) = TRUE;
				Dz1Error_set(errp, 0);
			}
		}
		else if (_get_file_size(ret->fp) == 0)
		{
			fclose(ret->fp);
			ret->fp = NULL;
			Dz1FileW_delete(fn);

			if (want_create == FALSE) Dz1Error_set(errp, ENOENT);
			else if ((*errp = Dz1StorageW_create(fn, ret)).code) ERR_OUT(errp);
			else
			{
				(*is_created) = TRUE;
				Dz1Error_set(errp, 0);
			}
		}
		else if ((*errp = _load_header(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1Storage_delAndSetNull, (void *)&ret);
	}
	return (Dz1StorageHandle *)ret;
}
#endif

Dz1StorageHandle *Dz1StorageA_new2(str_t path, str_t name, u32_t magic, bool_t *is_created, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *ret = NULL;

	char fn[4096];
	if ((*errp = Dz1FileName_concatPathName(Dz1ArrParam(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1StorageA_new(fn, magic, is_created, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1StorageHandle *Dz1StorageW_new2(wstr_t path, wstr_t name, u32_t magic, bool_t *is_created, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *ret = NULL;
	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathName(Dz1ArrParam(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1StorageW_new(fn, magic, is_created, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}
#endif

void Dz1Storage_del(Dz1StorageHandle *ptr)
{
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) return;
	if (p->fp)
	{
		_save_header(p);
		fflush(p->fp);
		Dz1FileStream_cancel(p->fp); p->fp = NULL;
	}
	Dz1Free(p);
}

void Dz1Storage_dump(Dz1StorageHandle *ptr, int tab)
{
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else
	{
		Dz1Thread_printf("{\n"); tab++;
		Dz1Thread_tprintf(tab, "Storage File Version = %08X\n", p->hdr.version);
		Dz1Thread_tprintf(tab, "Space Start Index = %u\n", p->hdr.space_start);
		Dz1Thread_tprintf(--tab, "}\n");
	}
}

static u32_t _unlink_from_space(FILE *fp, u32_t *space_start, Dz1Error *err)
{
	Dz1StorageFrag frag;
	u32_t work_idx = *space_start, ret = DZ1_STORAGE_FRAG_IDX_ERROR;
	DZ1_ERROR_SAFE_PTR(errp, err);
	// load first space frag
	if ((*errp = Dz1StorageFrag_loadInfo(fp, work_idx, &frag)).code) ERR_OUT(errp);
	else
	{
		// update space_start
		*space_start = frag.next_idx;

		// unlink frag & save
		frag.prev_idx = 0;
		frag.next_idx = 0;
		frag.chunk_size = 0;
		if ((*errp = Dz1StorageFrag_saveInfo(fp, work_idx, &frag)).code) ERR_OUT(errp);
		// check new space_start
		else if ( *space_start != 0)
		{	// load new first space frag
			if ((*errp = Dz1StorageFrag_loadInfo(fp, *space_start, &frag)).code) ERR_OUT(errp);
			else
			{	// make start frag save
				frag.prev_idx = 0;
				if ((*errp = Dz1StorageFrag_saveInfo(fp, *space_start, &frag)).code) ERR_OUT(errp);
				else ret = work_idx;
			}
		}
		else ret = work_idx;
	}
	return ret;
}

u32_t Dz1Storage_alloc(Dz1StorageHandle *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	u32_t ret = DZ1_STORAGE_FRAG_IDX_ERROR;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (p->hdr.space_start != 0)
		{
			if ((ret = _unlink_from_space(p->fp, &p->hdr.space_start, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
			else _save_header(p);
		}
		else if ((ret = Dz1StorageFrag_append(p->fp, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}

Dz1Error Dz1Storage_free(Dz1StorageHandle *ptr, u32_t idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (idx == DZ1_STORAGE_FRAG_IDX_NONE) ERR_SET_OUT(errp, EINVAL);
	else if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (p->hdr.space_start == idx) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1StorageFrag frag;
		if ((*errp = Dz1StorageFrag_loadInfo(p->fp, idx, &frag)).code) ERR_OUT(errp);
		else if (frag.prev_idx != 0) ERR_SET_OUT(errp, EPERM);
		else if ((*errp = Dz1StorageFrag_free(p->fp, idx, &p->hdr.space_start, &frag)).code) ERR_OUT(errp);
		else
		{
			_save_header(p);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}

static Dz1Error _add_entry(Dz1StorageChunkList *dst, u32_t idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageChunkEntry *node = Dz1StorageChunkEntry_new(idx, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageChunkEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1StorageChunkEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

Dz1StorageChunkList *Dz1Storage_getEntries(Dz1StorageHandle *ptr, Dz1Error *err)
{
	Dz1StorageChunkList *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StorageChunkList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1StorageFrag frag;
		u32_t idx = 1;
		pthread_cleanup_push(Dz1StorageChunkList_delAndSetNull, (void *)&ret);
		while((*errp = Dz1StorageFrag_loadInfo(p->fp, idx, &frag)).code == 0)
		{
			if (frag.prev_idx == DZ1_STORAGE_FRAG_IDX_NONE && idx != p->hdr.space_start)
			{
				if ((*errp = _add_entry(ret, idx)).code) ERR_OUT(errp);
			}
			idx++;
		}
		Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1StorageChunkList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Binary *Dz1Storage_loadBin(Dz1StorageHandle *ptr, u32_t entry_idx, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StorageFrag_loadBin(p->fp, entry_idx, errp)) == NULL) ERR_OUT(errp);

	return ret;
}

u8_t *Dz1Storage_load(Dz1StorageHandle *ptr, u32_t entry_idx, size_t *ret_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	u8_t *ret = NULL;
	Dz1Binary *bin = NULL;
	size_t _size = 0, *sz = ret_size ? ret_size : &_size;

	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1StorageFrag_loadBin(p->fp, entry_idx, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		ret = bin->data;
		*sz = bin->size;
		bin->data = NULL;
		bin->size = 0;
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}

	return ret;
}

Dz1Error Dz1Storage_saveBin(Dz1StorageHandle *ptr, u32_t entry_idx, Dz1Binary *src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1StorageFrag_saveBuf(p->fp, entry_idx, src->data, src->size, &p->hdr.space_start)).code) ERR_OUT(errp);
	else _save_header(p);
	return err;
}

Dz1Error Dz1Storage_save(Dz1StorageHandle *ptr, u32_t entry_idx, u8_t *data, size_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1StorageFrag_saveBuf(p->fp, entry_idx, data, size, &p->hdr.space_start)).code) ERR_OUT(errp);
	else _save_header(p);
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Init Blocks
static Dz1Error _add_block(Dz1StorageBlockList *dst, u32_t idx, Dz1StorageFrag *frag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageBlock *node = Dz1StorageBlock_new(idx, frag->prev_idx, frag->next_idx, 0, errp);
	if (node == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageBlock_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1StorageBlock_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _init_blocks(Dz1Storage *p, Dz1StorageBlockList *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t idx = 1;
	Dz1StorageFrag frag;
	while((*errp = Dz1StorageFrag_loadInfo(p->fp, idx, &frag)).code == 0)
	{
		if ((*errp = _add_block(dst, idx, &frag)).code) { ERR_OUT(errp); break; }
		else idx++;
	}
	Dz1Error_set(errp, 0);
	return err;
}
// Init Blocks
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Init Array
static Dz1StorageBlock *_find_block(Dz1StorageBlockList *list, u32_t idx)
{
	Dz1StorageBlock key = { idx };
	return list->find(list, &key);
}

static Dz1Error _init_array(Dz1StorageBlockList *src, Dz1StorageBlockArray *dst, u32_t entry_idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t idx = entry_idx;
	Dz1StorageBlock *node = NULL;
	while(idx != DZ1_STORAGE_FRAG_IDX_NONE && (node = _find_block(src, idx)) != NULL)
	{
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else node->flag++;
		idx = node->next_idx;
	}
	return err;
}
// Init Array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Init Archive
typedef struct InitArchiveArg
{
	Dz1StorageArchiveList *dst;
	u32_t space_start_idx;
} InitArchiveArg;

static Dz1Error _init_archive(void *ptr, Dz1StorageBlock *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	InitArchiveArg *arg = (InitArchiveArg *)ptr;
	Dz1StorageArchiveList *dst = arg->dst;
	if (p->idx != arg->space_start_idx && p->prev_idx == 0)
	{
		Dz1StorageArchive *node = Dz1StorageArchive_new(p->idx, errp);
		if (node == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1StorageArchive_delAndSetNull, (void *)&node);
			if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1StorageArchive_delAndSetNull, (void *)&node);
		}
	}
	return err;
}

static Dz1Error _build_archive(void *ptr, Dz1StorageArchive *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageBlockList *src = (Dz1StorageBlockList *)ptr;
	if ((*errp = _init_array(src, p->blocks, p->entry_idx)).code) ERR_OUT(errp);
	return err;
}

static Dz1Error _init_archives(Dz1StorageBlockList *src, Dz1StorageArchiveList *dst, u32_t space_start_idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	InitArchiveArg arg = { dst, space_start_idx };
	if ((*errp = src->travel(src, _init_archive, (void *)&arg)).code) ERR_OUT(errp);
	else if ((*errp = dst->travel(dst, _build_archive, (void *)src)).code) ERR_OUT(errp);
	return err;
}
// Init Archive
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Init Missings
static Dz1Error _init_missing(void *ptr, Dz1StorageBlock *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageBlockArray *dst = (Dz1StorageBlockArray *)ptr;
	if (p->flag == 0)
	{
		if ((*errp = dst->add(dst, p)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _init_missings(Dz1StorageBlockList *src, Dz1StorageBlockArray *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = src->travel(src, _init_missing, (void *)dst)).code) ERR_OUT(errp);
	return err;
}
// Init Missings
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Init Collisions
static Dz1Error _init_collision(void *ptr, Dz1StorageBlock *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1StorageBlockArray *dst = (Dz1StorageBlockArray *)ptr;
	if (p->flag > 1)
	{
		if ((*errp = dst->add(dst, p)).code) ERR_OUT(errp);
	}
	return err;
}

static Dz1Error _init_collisions(Dz1StorageBlockList *src, Dz1StorageBlockArray *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = src->travel(src, _init_collision, (void *)dst)).code) ERR_OUT(errp);
	return err;
}
// Init Collisions
///////////////////////////////////////////////////////////////////////////////

Dz1StorageInfo *Dz1Storage_analysis(Dz1StorageHandle *ptr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	Dz1StorageInfo *ret = NULL;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1StorageInfo_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StorageInfo_delAndSetNull, (void *)&ret);
		if ((*errp = _init_blocks(p, ret->blocks)).code) ERR_OUT(errp);
		else if ((*errp = _init_array(ret->blocks, ret->spaces, p->hdr.space_start)).code) ERR_OUT(errp);
		else if ((*errp = _init_archives(ret->blocks, ret->archives, p->hdr.space_start)).code) ERR_OUT(errp);
		else if ((*errp = _init_missings(ret->blocks, ret->missings)).code) ERR_OUT(errp);
		else if ((*errp = _init_collisions(ret->blocks, ret->collisions)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1StorageInfo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _build_space(Dz1Storage *p, Dz1StorageBlockList *dst)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1StorageFrag frag;
	u32_t idx = p->hdr.space_start;
	while(idx != 0 && (*errp = Dz1StorageFrag_loadInfo(p->fp, idx, &frag)).code == 0)
	{
		if ((*errp = _add_block(dst, idx, &frag)).code) { ERR_OUT(errp); break; }
		idx = frag.next_idx;
	}

	return err;
}

typedef struct SpaceSortArg
{
	FILE			*fp;
	Dz1StorageBlock	*entry[2];
	Dz1StorageFrag	 frag;
} SpaceSortArg;

static Dz1Error _link_spaces(void *ptr, Dz1StorageBlock *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SpaceSortArg *arg = (SpaceSortArg *)ptr;
	if (arg->entry[0] == NULL)
	{
		arg->entry[0] = p;

		if (arg->entry[0]->prev_idx != 0)
		{
			arg->entry[0]->prev_idx = 0;
			arg->entry[0]->flag = 1;
		}
	}
	else if (arg->entry[1] == NULL)
	{
		arg->entry[1] = p;

		if (arg->entry[0]->next_idx != p->idx)
		{
			arg->entry[0]->next_idx = p->idx;
			arg->entry[0]->flag = 1;
		}
		if (arg->entry[1]->prev_idx != arg->entry[0]->idx)
		{
			arg->entry[1]->prev_idx = arg->entry[0]->idx;
			arg->entry[1]->flag = 1;
		}
	}
	else
	{
		arg->entry[0] = arg->entry[1];
		arg->entry[1] = p;

		if (arg->entry[0]->next_idx != p->idx)
		{
			arg->entry[0]->next_idx = p->idx;
			arg->entry[0]->flag = 1;
		}
		if (arg->entry[1]->prev_idx != arg->entry[0]->idx)
		{
			arg->entry[1]->prev_idx = arg->entry[0]->idx;
			arg->entry[1]->flag = 1;
		}
	}
	Dz1Error_set(errp, 0);
	return err;
}

static Dz1Error _save_spaces(void *ptr, Dz1StorageBlock *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	SpaceSortArg *arg = (SpaceSortArg *)ptr;
	Dz1StorageFrag *frag = &arg->frag;
	if (p->flag)
	{
		frag->prev_idx = p->prev_idx;
		frag->next_idx = p->next_idx;
		if ((*errp = Dz1StorageFrag_saveInfo(arg->fp, p->idx, frag)).code) ERR_OUT(errp);
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1Sotrage_sort(Dz1StorageHandle *ptr)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Storage *p = (Dz1Storage *)ptr;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1StorageBlockList *list = Dz1StorageBlockList_new(errp);
		if (list == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1StorageBlockList_delAndSetNull, (void *)&list);
			if ((*errp = _build_space(p, list)).code) ERR_OUT(errp);
			else if (list->count(list) > 1)
			{
				SpaceSortArg arg = { p->fp, { NULL, NULL } };
				if ((*errp = list->travel(list, _link_spaces, (void *)&arg)).code) ERR_OUT(errp);
				else
				{
					Dz1StorageBlock *head = list->getHead(list);
					p->hdr.space_start = head->idx;

					arg.entry[1]->next_idx = 0;
					if ((*errp = list->travel(list, _save_spaces, (void *)&arg)).code) ERR_OUT(errp);
					_save_header(p);
				}
			}
			pthread_cleanup_pop(1); // (Dz1StorageBlockList_delAndSetNull, (void *)&list);
		}
	}
	return err;
}

static void _set_ret_error(void *ptr)
{
	u32_t *v = (u32_t *)ptr;
	(*v) = DZ1_STORAGE_FRAG_IDX_ERROR;
}

u32_t Dz1Storage_import(Dz1StorageHandle *ptr, Dz1Stream *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t ret = DZ1_STORAGE_FRAG_IDX_ERROR;

	if ((ret = Dz1Storage_alloc(ptr, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
	else
	{
		Dz1Stream *ous = NULL;
		Dz1SotrageAllocCancelArg arg = { ptr, ret };
		pthread_cleanup_push(_set_ret_error, (void *)&ret);
		pthread_cleanup_push(Dz1Storage_allocCancel, (void *)&arg);

		if ((ous = Dz1StorageStream_open(ptr, ret, Dz1StreamFileMode_WR, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t sz, status, written = 0;
			u8_t buf[4096];
			pthread_cleanup_push(Dz1Stream_closeAndSetNull, (void *)&ous);
			while((sz = Dz1Stream_read(src, buf, 4096, errp)) > 0)
			{
				if ((status = Dz1Stream_write(ous, buf, sz, errp)) <= 0) 
				{
					written = -1;
					if (status == 0) ERR_SET_OUT(errp, EPIPE); else ERR_OUT(errp);
					break;
				}
				else
				{
					written += status;
					if (sz != status) { ERR_SET_OUT(errp, ENOMEM); break; }
				}
			}

			if (written < 0) ERR_OUT(errp); else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1OutStream_closeAndSetNull, (void *)&ous);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Storage_allocCancel, (void *)&arg);
		pthread_cleanup_pop(errp->code); // (_set_ret_error, (void *)&ret);
	}
	return ret;
}

#include "dz1_vfs.h"
#include "dz1_vfs_codec.h"
#include "dz1_vfs_util.h"

#define DZ1_VFS_ROOT_IDX				1
#define _mk_magic(a, b, c, d)			(((u32_t)(a) & 0xFF) << 24 | \
										 ((u32_t)(b) & 0xFF) << 16 | \
										 ((u32_t)(c) & 0xFF) << 8 | \
										 ((u32_t)(d) & 0xFF))

typedef struct StorageAllocCancelArg
{
	Dz1StorageHandle *io;
	u32_t cancel_idx;
} StorageAllocCancelArg;

static void _storage_alloc_cancel(void *ptr)
{
	StorageAllocCancelArg *arg = (StorageAllocCancelArg *)ptr;
	Dz1Storage_free(arg->io, arg->cancel_idx);
}

static Dz1Binary *_create_root_dir_and2_stream(Dz1Vfs *vfs, u32_t idx, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	Dz1VfsDir *p = NULL;
	if ((p = Dz1VfsDir_new(idx, DZ1_STORAGE_FRAG_IDX_NONE, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&vfs->root);
		if ((p->tags = Dz1MetaTagData_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret = Dz1VfsDir_toStream(p, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1VfsDir_delAndSetNull, (void *)&vfs->root);
	}
	return ret;
}

static Dz1Error _format_vfs(Dz1Vfs *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t idx = Dz1Storage_alloc(p->io, errp);												// Allocate storage to root dir
	if (idx == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
	else
	{
		StorageAllocCancelArg arg = { p->io, idx };
		pthread_cleanup_push(_storage_alloc_cancel, (void *)&arg);							// Allocation cancel for root dir

		if (idx != DZ1_VFS_ROOT_IDX) ERR_SET_OUT(errp, EFAULT);								// check index number
		else
		{
			Dz1Binary *bin = NULL;															// Binary for root dir
			if ((bin = _create_root_dir_and2_stream(p, idx, errp)) == NULL) ERR_OUT(errp);	// create root dir and encode it
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);				// delete stream data for root dir

				if ((*errp = Dz1Storage_saveBin(p->io, idx, bin)).code) ERR_OUT(errp);		// write root dir to storage
				else Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&root_dir_bin);
			}
		}
		pthread_cleanup_pop(errp->code); // (_storage_alloc_cancel, (void *)&arg);
	}
	return err;
}

static Dz1Vfs *_Dz1Vfs_open(Dz1StorageHandle **h, bool_t is_created, Dz1Error *err)
{
	Dz1Vfs *ret = NULL;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((ret = Dz1Vfs_new(DZ1_STORAGE_FRAG_IDX_NONE, *h, errp)) == NULL) ERR_OUT(errp);
	else
	{
		*h = NULL;
		pthread_cleanup_push(Dz1Vfs_delAndSetNull, (void *)&ret);
		if (is_created)
		{
			if ((*errp = _format_vfs(ret)).code) ERR_OUT(errp);
		}
		else
		{
			if ((ret->root = Dz1VfsHandleDirList_open(ret->dirHandles, ret->io, DZ1_VFS_ROOT_IDX, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Vfs_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Vfs *Dz1Vfs_open(str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Vfs *ret = NULL;
	bool_t is_created = FALSE;
	Dz1StorageHandle *h = Dz1Storage_new(fn, _mk_magic('j', 'V', 'F', 'S'), &is_created, errp);
	if (h == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Storage_delAndSetNull, (VOID *)&h);
		if ((ret = _Dz1Vfs_open(&h, is_created, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Storage_delAndSetNull, (VOID *)&h);
	}
	return ret;
}

Dz1Vfs *Dz1Vfs_open2(str_t path, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Vfs *ret = NULL;

	char fn[4096];
	if ((*errp = Dz1FileName_concatPathName(fn, path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1Vfs_open(fn, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}

#ifdef WIN32
Dz1Vfs *Dz1VfsW_open(wstr_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Vfs *ret = NULL;
	bool_t is_created = FALSE;
	Dz1StorageHandle *h = Dz1StorageW_new(fn, _mk_magic('j', 'V', 'F', 'S'), &is_created, errp);
	if (h == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Storage_delAndSetNull, (VOID *)&h);
		if ((ret = _Dz1Vfs_open(&h, is_created, errp)) == NULL) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Storage_delAndSetNull, (VOID *)&h);
	}
	return ret;
}

Dz1Vfs *Dz1VfsW_open2(wstr_t path, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Vfs *ret = NULL;

	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathName(fn, path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1VfsW_open(fn, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ret;
}
#endif

void Dz1Vfs_close(Dz1Vfs *p)
{
	if (p == NULL) return;
	if (p->io) Dz1Storage_delAndSetNull(&p->io);
	Dz1Vfs_del(p);
}
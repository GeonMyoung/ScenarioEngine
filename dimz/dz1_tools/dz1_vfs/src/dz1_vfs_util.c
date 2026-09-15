#include "dz1_vfs_codec.h"
#include "dz1_vfs_util.h"

static Dz1Error _encode_dir_and_save(Dz1StorageHandle *io, u32_t idx, Dz1VfsDir *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Binary *bin = Dz1VfsDir_toStream(p, NULL, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((*errp = Dz1Storage_saveBin(io, idx, bin)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

static Dz1Error _create_dir_and_save(Dz1StorageHandle *io, u32_t idx, u32_t parent_idx)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1VfsDir *p = Dz1VfsDir_new(idx, parent_idx, NULL, errp);
	if (p == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&p);

		if ((p->tags = Dz1MetaTagData_new(errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _encode_dir_and_save(io, idx, p)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1VfsDir_delAndSetNull, (void *)&p);
	}
	return err;
}

static Dz1VfsDir *_load_dir_and_decode(Dz1StorageHandle *io, u32_t idx, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1VfsDir *ret = NULL;
	Dz1Binary *bin = Dz1Storage_loadBin(io, idx, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((ret = Dz1VfsDir_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}

static Dz1VfsHandleDirEntry *_load_dir_and_create_handle(Dz1VfsHandleDirList *dst, u32_t idx, Dz1StorageHandle *io, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1VfsHandleDirEntry *ret = NULL, *node = NULL;
	if ((ret = Dz1VfsHandleDirEntry_new(idx, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDirEntry_delAndSetNull, (void *)&node);
		if ((node->sync = Dz1Sync_new(errp)) == NULL) ERR_OUT(errp);
		else if ((node->source = _load_dir_and_decode(io, idx, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			ret = node;
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1VfsHandleDirEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

///////////////////////////////////////
// DIR GetHandle
static u32_t Dz1VfsHandleDirEntry_getHandle(Dz1VfsHandleDirEntry *node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t ret = -1;
	Dz1VfsHandleDirInfoList *handles = node->handles;
	Dz1VfsHandleDir *handle = Dz1VfsHandleDir_new(handles->count(handles), FALSE, FALSE, FALSE, errp);
	if (handle == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDir_delAndSetNull, (void *)&handle);
		if ((*errp = handles->add(handles, handle)).code) ERR_OUT(errp);
		else
		{
			ret = handle->handle_id;
			handle = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1VfsHandleDir_delAndSetNull, (void *)&handle);
	}
	return ret;
}
// DIR GetHandle
///////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DIR Open
static Dz1Error _Dz1VfsHandleDirList_open(Dz1VfsHandleDirList *list, u32_t idx, Dz1VfsHandleID *id, Dz1StorageHandle *io)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsHandleDirEntry key = { idx }, *node = NULL;
	if ((node = list->find(list, &key)) == NULL)
	{	// create
		if		((node = _load_dir_and_create_handle(list, idx, io, errp)) == NULL) ERR_OUT(errp);
		else if ((id->handle = Dz1VfsHandleDirEntry_getHandle(node, errp)) == -1) ERR_OUT(errp);
		else
		{
			id->idx = idx;
			Dz1Error_set(errp, 0);
		}
	}
	else
	{	// exist
		Dz1Sync_lock(node->sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)node->sync);
		
		if ((id->handle = Dz1VfsHandleDirEntry_getHandle(node, errp)) == -1) ERR_OUT(errp);
		else
		{
			id->idx = node->idx;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)node->sync);
	}
	return err;
}
Dz1VfsAccess *Dz1VfsHandleDirList_open(Dz1VfsHandleDirList *list, u32_t idx, Dz1StorageHandle *io, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1VfsAccess *ret = Dz1VfsAccess_new(Dz1VfsAccessPresent_dir, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1VfsHandleID *id = NULL;
		pthread_cleanup_push(Dz1VfsAccess_delAndSetNull, (void *)&ret);

		if ((ret->x.dir = id = Dz1VfsHandleID_new(DZ1_STORAGE_FRAG_IDX_NONE, -1, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = _Dz1VfsHandleDirList_open(list, idx, id, io)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1VfsAccess_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// DIR Open
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DIR Close
static Dz1Error _close_critical(Dz1VfsHandleDirEntry *node, Dz1VfsHandleID *dir)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsHandleDirInfoList *handles = node->handles;
	Dz1VfsHandleDir key = { dir->handle }, *handle = handles->extract(handles, &key);
	if (handle == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		pthread_cleanup_push(Dz1VfsHandleDir_delAndSetNull, (void *)&handle);
		Dz1Thread_printf("@@@ Handle Close\n");
		pthread_cleanup_pop(1); // (Dz1VfsHandleDir_delAndSetNull, (void *)&handle);
	}
	return err;
}

static Dz1Error _Dz1VfsHandleDirList_close(Dz1VfsHandleDirList *list, Dz1VfsAccess *access)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1VfsHandleID *dir = access->x.dir;
	Dz1VfsHandleDirEntry key = { dir->idx }, *node = list->find(list, &key);
	if (node == NULL) ERR_SET_OUT(errp, EINTR);
	else
	{

		Dz1Sync_lock(node->sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)node->sync);

		if ((*errp = _close_critical(node, dir)).code) ERR_OUT(errp);
		else
		{
			dir->idx = DZ1_STORAGE_FRAG_IDX_NONE;
			dir->handle = -1;
		}

		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)node->sync);
	}
	return err;
}

Dz1Error Dz1VfsHandleDirList_close(Dz1VfsHandleDirList *list, Dz1VfsAccess *access)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (access->present != Dz1VfsAccessPresent_dir) ERR_SET_OUT(errp, EINVAL);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1VfsAccess_del, (void *)access);
		if ((*errp = _Dz1VfsHandleDirList_close(list, access)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1VfsAccess_del, (void *)access);
	}
	return err;
}
// DIR Close
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
// Tag Changed
static Dz1Error _dir_handle_set_tagChanged(void *ptr, Dz1VfsHandleDir *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t origin = *(u32_t *)ptr;
	if (p->handle_id != origin) p->tagChanged = TRUE;
	return err;
}

static Dz1Error _dir_handles_set_tagChanged(Dz1VfsHandleDirInfoList *dst, u32_t origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = dst->travel(dst, _dir_handle_set_tagChanged, (void *)&origin)).code) ERR_OUT(errp);
	return err;
}
// Tag Changed
///////////////////////////////////////

///////////////////////////////////////
// Child Changed
static Dz1Error _dir_handle_set_childChanged(void *ptr, Dz1VfsHandleDir *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t origin = *(u32_t *)ptr;
	if (p->handle_id != origin) p->childChanged = TRUE;
	return err;
}

static Dz1Error _dir_handles_set_childChanged(Dz1VfsHandleDirInfoList *dst, u32_t origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = dst->travel(dst, _dir_handle_set_childChanged, (void *)&origin)).code) ERR_OUT(errp);
	return err;
}
// Child Changed
///////////////////////////////////////

///////////////////////////////////////
// File Changed
static Dz1Error _dir_handle_set_fileChanged(void *ptr, Dz1VfsHandleDir *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u32_t origin = *(u32_t *)ptr;
	if (p->handle_id != origin) p->fileChanged = TRUE;
	return err;
}

static Dz1Error _dir_handles_set_fileChanged(Dz1VfsHandleDirInfoList *dst, u32_t origin)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = dst->travel(dst, _dir_handle_set_fileChanged, (void *)&origin)).code) ERR_OUT(errp);
	return err;
}
// File Changed
///////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// MKDIR
static Dz1Error _mkdir_critical(Dz1VfsHandleDirEntry *node, Dz1VfsHandleID *dir, Dz1Asn1UTF8Str *name, Dz1StorageHandle *io)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1VfsHandleDirInfoList *handles = node->handles;
	Dz1VfsHandleDir hkey = { dir->handle }, *handle = handles->find(handles, &hkey);
	if (handle == NULL) ERR_SET_OUT(errp, EINTR);
	else
	{
		Dz1VfsDir *source = node->source;
		Dz1VfsChildList *childes = source->dirs;

		Dz1VfsChildNode ckey = { name }, *child = childes->find(childes, &ckey);
		if (child != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((child = Dz1VfsChildNode_new(NULL, DZ1_STORAGE_FRAG_IDX_NONE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1VfsChildNode_delAndSetNull, (void *)&child);
			if ((child->name = Dz1Asn1UTF8Str_clone(name, errp)) == NULL) ERR_OUT(errp);

			else if ((child->idx = Dz1Storage_alloc(io, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
			else
			{
				Dz1SotrageAllocCancelArg arg = { io, child->idx };
				pthread_cleanup_push(Dz1Storage_allocCancel, (void *)&arg);
				// Save Changes
				if ((*errp = _create_dir_and_save(io, child->idx, node->idx)).code) ERR_OUT(errp);
				else if ((*errp = _encode_dir_and_save(io, node->idx, source)).code) ERR_OUT(errp);
				// Add child
				else if ((*errp = childes->add(childes, child)).code) ERR_OUT(errp);
				else
				{
					child = NULL;	
					Dz1Error_set(errp, 0);
				}
				// inform to other handles
				_dir_handles_set_childChanged(node->handles, dir->handle);
				Dz1Sync_signal(node->sync);

				pthread_cleanup_pop(errp->code); // (Dz1Storage_allocCancel, (void *)&arg);
			}
			pthread_cleanup_pop(1); // (Dz1VfsChildNode_delAndSetNull, (void *)&child);
		}
	}
	return err;
}

Dz1Error Dz1VfsHandleDirList_mkdir(Dz1VfsHandleDirList *list, Dz1VfsAccess *access, Dz1Asn1UTF8Str *name, Dz1StorageHandle *io)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (access->present != Dz1VfsAccessPresent_dir) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1VfsHandleID *dir = access->x.dir;
		Dz1VfsHandleDirEntry key = { dir->idx }, *node = list->find(list, &key);
		if (node == NULL) ERR_SET_OUT(errp, EINTR);
		else
		{

			Dz1Sync_lock(node->sync);
			pthread_cleanup_push(Dz1Sync_lockCancel, (void *)node->sync);

			if ((*errp = _mkdir_critical(node, dir, name, io)).code) ERR_OUT(errp);

			pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)node->sync);
		}
	}
	return err;
}
// MKDIR
///////////////////////////////////////////////////////////////////////////////

static Dz1VfsHandleDirEntry *_chdir_critical(Dz1VfsHandleDirEntry *node, Dz1VfsHandleID *dir, Dz1Asn1UTF8Str *name, Dz1StorageHandle *io, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1VfsHandleDirInfoList *handles = node->handles;
	Dz1VfsHandleDir hkey = { dir->handle }, *handle = handles->find(handles, &hkey);
	if (handle == NULL) ERR_SET_OUT(errp, EINTR);
	else
	{
		Dz1VfsDir *source = node->source;
		Dz1VfsChildList *childes = source->dirs;

		Dz1VfsChildNode ckey = { name }, *child = childes->find(childes, &ckey);
		if (child != NULL) ERR_SET_OUT(errp, EEXIST);
		else if ((child = Dz1VfsChildNode_new(NULL, DZ1_STORAGE_FRAG_IDX_NONE, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1VfsChildNode_delAndSetNull, (void *)&child);
			if ((child->name = Dz1Asn1UTF8Str_clone(name, errp)) == NULL) ERR_OUT(errp);

			else if ((child->idx = Dz1Storage_alloc(io, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
			else
			{
				Dz1SotrageAllocCancelArg arg = { io, child->idx };
				pthread_cleanup_push(Dz1Storage_allocCancel, (void *)&arg);
				// Save Changes
				if ((*errp = _create_dir_and_save(io, child->idx, node->idx)).code) ERR_OUT(errp);
				else if ((*errp = _encode_dir_and_save(io, node->idx, source)).code) ERR_OUT(errp);
				// Add child
				else if ((*errp = childes->add(childes, child)).code) ERR_OUT(errp);
				else
				{
					child = NULL;	
					Dz1Error_set(errp, 0);
				}
				// inform to other handles
				_dir_handles_set_childChanged(node->handles, dir->handle);
				Dz1Sync_signal(node->sync);

				pthread_cleanup_pop(errp->code); // (Dz1Storage_allocCancel, (void *)&arg);
			}
			pthread_cleanup_pop(1); // (Dz1VfsChildNode_delAndSetNull, (void *)&child);
		}
	}
}

static u32_t _find_child_ciritical(Dz1VfsDir *source, Dz1Asn1UTF8Str *name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t ret = DZ1_STORAGE_FRAG_IDX_ERROR;
	Dz1VfsChildNode key = { name }, *node = source->dirs->find(source->dirs, &key);
	if (node != NULL) ret = node->idx;
	return ret;

}
static u32_t _find_child(Dz1VfsHandleDirList *list, Dz1VfsHandleID *dir, Dz1Asn1UTF8Str *name, Dz1Error *err)
{
	u32_t ret = DZ1_STORAGE_FRAG_IDX_ERROR;
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1VfsHandleDirEntry key = { dir->idx }, *node = list->find(list, &key);
	if (node == NULL) ERR_SET_OUT(errp, EINTR);
	else
	{
		Dz1Sync_lock(node->sync);
		pthread_cleanup_push(Dz1Sync_lockCancel, (void *)node->sync);
		if ((ret = _find_child_ciritical(node->source, name, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1Sync_lockCancel, (void *)node->sync);
	}
	return ret;
}

Dz1Error Dz1VfsHandleDirList_chdir(Dz1VfsHandleDirList *list, Dz1VfsAccess *access, Dz1Asn1UTF8Str *name, Dz1StorageHandle *io)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (access->present != Dz1VfsAccessPresent_dir) ERR_SET_OUT(errp, EINVAL);
	else
	{
		u32_t idx = DZ1_STORAGE_FRAG_IDX_NONE;
		Dz1VfsHandleID *dir = access->x.dir;
		if ((idx = _find_child(list, dir, name, errp)) == DZ1_STORAGE_FRAG_IDX_ERROR) ERR_OUT(errp);
		else
		{
			_Dz1VfsHandleDirList_close(list, access);
			if ((*errp = _Dz1VfsHandleDirList_open(list, idx, dir, io)).code) ERR_OUT(errp);
		}
	}
	return err;
}
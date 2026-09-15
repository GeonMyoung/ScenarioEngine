#include "dz1_task_gen_args_util.h"

///////////////////////////////////////////////////////////////////////////////
// Stream support
static Dz1Error _GenArgs2LibraryInfo_rebuild(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	GenArgs2LibraryRefIndex *inorder = (GenArgs2LibraryRefIndex *)ptr;
	if ((*errp = inorder->add(inorder, p)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

bool_t GenArgs2LibraryInfo_rebuild(GenArgs2LibraryInfo *p, void *param, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2LibraryList *tbl = p->table;
	if ((*errp = tbl->travel(tbl, _GenArgs2LibraryInfo_rebuild, (void *)p->inorder)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// Stream support
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Add
static void GenArgs2LibraryInfo_addCancel(void *ptr)
{
	Dz1ListAddCancelArg *arg = (Dz1ListAddCancelArg *)ptr;
	GenArgs2LibraryList *table = (GenArgs2LibraryList *)arg->list;
	GenArgs2LibraryEntry **node = (GenArgs2LibraryEntry **)arg->node;
	if (node != NULL && *node != NULL) table->extract(table, *node);
}

static bool_t GenArgs2LibraryInfo_addCheck(GenArgs2LibraryRefIndex *inorder, GenArgs2LibraryEntry *node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (node->order == 0)
	{
		GenArgs2LibraryEntry *last = inorder->getTail(inorder);
		if (last == NULL) node->order = 0; else node->order = last->order + 10;
	}
	else if (inorder->find(inorder, node) != NULL) ERR_SET_OUT(errp, EEXIST);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error GenArgs2LibraryInfo_add(GenArgs2LibraryInfo *info, GenArgs2LibraryEntry *node)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (info == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = info->table->add(info->table, node)).code) ERR_OUT(errp);
	else
	{

		Dz1ListAddCancelArg arg = { info->table, (void **)&node }; // modified by gm 20230602 - explicit type cating node 

		pthread_cleanup_push(GenArgs2LibraryInfo_addCancel, (void *)&arg);

		if (GenArgs2LibraryInfo_addCheck(info->inorder, node, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = info->inorder->add(info->inorder, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GenArgs2LibraryInfo_addCancel, (void *)&arg);
	}
	return err;
}
// Add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Remove
static void GenArgs2LibraryInfo_remove(GenArgs2LibraryInfo *info, GenArgs2LibraryEntry *key)
{
	if (info != NULL && key != NULL)
	{
		GenArgs2LibraryList *table = info->table;
		GenArgs2LibraryEntry *node = table->extract(table, key);
		if (node != NULL)
		{
			pthread_cleanup_push(GenArgs2LibraryEntry_delAndSetNull, (void *)&node);

			info->inorder->remove(info->inorder, node);

			pthread_cleanup_pop(1); // (GenArgs2LibraryEntry_delAndSetNull, (void *)&node);
		}
	}
}
// Remove
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Get Array
static GenArgs2LibraryEntry **GenArgs2LibraryInfo_get_array(GenArgs2LibraryInfo *info, u32_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2LibraryEntry **ret = NULL;
	if (info != NULL)
	{
//		GenArgs2LibraryList *list = info->table;
		GenArgs2LibraryRefIndex *list = info->inorder;
		if (list == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((ret = list->get_array(list, ret_cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return ret;
}
// Get Array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Find
static GenArgs2LibraryEntry *GenArgs2LibraryInfo_find(GenArgs2LibraryInfo *info, GenArgs2LibraryEntry *key)
{
	GenArgs2LibraryEntry *ret = NULL;
	if (info != NULL && key != NULL)
	{
		GenArgs2LibraryList *list = NULL;
		if ((list = info->table) != NULL)
			ret = list->find(list, key);
	}
	return ret;
}
// Find
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Extract
static GenArgs2LibraryEntry *GenArgs2LibraryInfo_extract(GenArgs2LibraryInfo *info, GenArgs2LibraryEntry *key)
{
	GenArgs2LibraryEntry *ret = NULL;
	if (info != NULL && key != NULL)
	{
		GenArgs2LibraryList *table = NULL;
		GenArgs2LibraryRefIndex *inorder = NULL;
		if ((table = info->table) != NULL && (inorder = info->inorder) != NULL)
		{
			if ((ret = table->extract(table, key)) != NULL)
				inorder->extract(inorder, ret);
		}
	}
	return ret;
}
// Extract
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfo_new
GenArgs2LibraryInfo *GenArgs2LibraryInfo_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryInfo *__internal_ret = (GenArgs2LibraryInfo *)Dz1Calloc(sizeof(GenArgs2LibraryInfo), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenArgs2LibraryInfo_delAndSetNull, (void *)&__internal_ret);

		if ((__internal_ret->table = GenArgs2LibraryList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else if ((__internal_ret->inorder = GenArgs2LibraryRefIndex_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
		else
		{
			__internal_ret->add			= GenArgs2LibraryInfo_add;
			__internal_ret->remove		= GenArgs2LibraryInfo_remove;
			__internal_ret->find		= GenArgs2LibraryInfo_find;
			__internal_ret->extract		= GenArgs2LibraryInfo_extract;
			__internal_ret->get_array	= GenArgs2LibraryInfo_get_array;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryInfo_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}
// GenArgs2LibraryInfo_new
///////////////////////////////////////////////////////////////////////////////

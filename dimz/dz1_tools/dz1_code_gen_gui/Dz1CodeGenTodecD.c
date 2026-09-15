#include "Dz1CodeGenTodecDef.h"

///////////////////////////////////////////////////////////////////////////////
// Add
// typedef struct SpecTableAddCancelArg
// {
// 	IncludePathTable		*table;
// 	IncludePathEntry		*node;
// } SpecTableAddCancelArg;
// 
// static void SpecTable_addCancel(void *ptr)
// {
// 	SpecTableAddCancelArg *arg = (SpecTableAddCancelArg *)ptr;
// 	arg->table->extract(arg->table, arg->node);
// }
// 
// static Dz1Error GeneralIncludeSpec_add(GeneralIncludeSpec *p, IncludePathEntry *node)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	if (p == NULL || p->table == NULL || node == NULL) ERR_SET_OUT(errp, EINVAL);
// 	else if ((*errp = p->table->add(p->table, node)).code) ERR_OUT(errp);
// 	else
// 	{
// 		SpecTableAddCancelArg arg = { p->table, node };
// 		pthread_cleanup_push(SpecTable_addCancel, (void *)&arg);
// 		if ((*errp = p->seq->add(p->seq, node)).code) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(errp->code); // (SpecTable_addCancel, (void *)&arg);
// 	}
// 	return err;
// }
// Add
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Remove
// static void GeneralIncludeSpec_remove(GeneralIncludeSpec *p, IncludePathEntry *key)
// {
// 	IncludePathEntry *node = NULL;
// 	if (p->table != NULL && key != NULL && (node = p->table->extract(p->table, key)) != NULL)
// 	{
// 		pthread_cleanup_push(IncludePathEntry_delAndSetNull, (void *)&node);
// 		p->seq->extract(p->seq, node);
// 		pthread_cleanup_pop(1); // (IncludePathEntry_delAndSetNull, (void *)&node);
// 	}
// }
// Remove
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Find
// static IncludePathEntry *GeneralIncludeSpec_find(GeneralIncludeSpec *p, IncludePathEntry *key)
// {
// 	IncludePathEntry *ret = NULL;
// 	if (p != NULL && p->table != NULL)
// 		ret = p->table->find(p->table, key);
// 	return ret;
// }
// Find
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Get Array
// static IncludePathEntry **GeneralIncludeSpec_get_array(GeneralIncludeSpec *p, size_t *ret_cnt, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	IncludePathEntry **ret = NULL;
// 	if (p != NULL && p->table != NULL)
// 	{
// 		if ((ret = p->table->get_array(p->table, ret_cnt, errp)) == NULL) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 	}
// 	return ret;
// }
// Get Array
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// New
// GeneralIncludeSpec *GeneralIncludeSpec_new(Dz1Error *err)
// {
// 	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
// 	GeneralIncludeSpec *__internal_ret = (GeneralIncludeSpec *)Dz1Calloc(sizeof(GeneralIncludeSpec), 1, errp);
// 	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
// 	else
// 	{
// 		pthread_cleanup_push(GeneralIncludeSpec_delAndSetNull, (void *)&__internal_ret);
// 
// 		if ((__internal_ret->table = IncludePathTable_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
// 		else if ((__internal_ret->seq = IncludePathList_new(errp)) == NULL) ERR_OUT(errp); // ASN OPTIONAL
// 		else
// 		{
// 			__internal_ret->add = GeneralIncludeSpec_add;
// 			__internal_ret->remove = GeneralIncludeSpec_remove;
// 			__internal_ret->find = GeneralIncludeSpec_find;
// 			__internal_ret->get_array = GeneralIncludeSpec_get_array;
// 			ERR_CLEAR(errp);
// 		}
// 		pthread_cleanup_pop(ERR_PROBE(errp)); // (GeneralIncludeSpec_delAndSetNull, (void *)&__internal_ret)
// 	}
// 	return __internal_ret;
// }
// New
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Clone
// static Dz1Error _IncludeSpec_cloneAndAdd(GeneralIncludeSpec *dst, IncludePathEntry *src)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 	IncludePathEntry *node = IncludePathEntry_clone(src, errp);
// 	if (node == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		pthread_cleanup_push(IncludePathEntry_delAndSetNull, (void *)&node);
// 		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
// 		else
// 		{
// 			node = NULL;
// 			Dz1Error_set(errp, 0);
// 		}
// 		pthread_cleanup_pop(1); // (IncludePathEntry_delAndSetNull, (void *)&node);
// 	}
// 	return err;
// }
// 
// static Dz1Error _GeneralIncludeSpec_clone(GeneralIncludeSpec *dst, GeneralIncludeSpec *src)
// {
// 	DZ1_ERROR_SAFE_VAR(errp, err);
// 
// 	size_t cnt = 0;
// 	IncludePathEntry **arr = src->seq->get_array(src->seq, &cnt, errp);
// 	if (arr == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		size_t i;
// 		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&arr);
// 		for (i = 0; errp->code == 0 && i < cnt; i++)
// 		{
// 			if ((*errp = _IncludeSpec_cloneAndAdd(dst, arr[i])).code) ERR_OUT(errp);
// 			else Dz1Error_set(errp, 0);
// 		}
// 		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&arr);
// 	}
// 	return err;
// }
// 
// GeneralIncludeSpec *GeneralIncludeSpec_clone(GeneralIncludeSpec *src, Dz1Error *err)
// {
// 	GeneralIncludeSpec *ret = NULL;
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
// 	else if ((ret = GeneralIncludeSpec_new(errp)) == NULL) ERR_OUT(errp);
// 	else
// 	{
// 		pthread_cleanup_push(GeneralIncludeSpec_delAndSetNull, (void *)&ret);
// 
// 		if ((*errp = _GeneralIncludeSpec_clone(ret, src)).code) ERR_OUT(errp);
// 		else Dz1Error_set(errp, 0);
// 
// 		pthread_cleanup_pop(ERR_PROBE(errp)); // (GeneralIncludeSpec_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }
// Clone
///////////////////////////////////////////////////////////////////////////////


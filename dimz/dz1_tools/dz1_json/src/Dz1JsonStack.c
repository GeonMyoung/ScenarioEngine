#include <dz1_thread_stdio.h>
#include "Dz1JsonStructUtil.h"
#include "Dz1JsonStack.h"

static void _push_stk(Dz1JsonEnv *psr, Dz1JsonStack **nstk)
{
//	Dz1Thread_printf(">>> Call Sub Parser = "); Dz1JsonStack_dump( (*nstk) , 0);
	(*nstk)->next = psr->stk;
	psr->stk = (*nstk);
	(*nstk) = NULL;
}

bool_t Dz1JsonEnv_stack_pushPair(Dz1JsonEnv *psr, Dz1JsonSpecEntry *p_spe, void *p_dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStack *nstk = Dz1JsonStack_new(NULL, NULL, errp);
	if (nstk == NULL) ERR_OUT(errp);
	else
	{
		Dz1JsonStackData *d = NULL;
		pthread_cleanup_push(Dz1JsonStack_delAndSetNull, (void *)&nstk);

		if ((nstk->dst_var = Dz1JsonVarBind_new(NULL, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((nstk->data = d = Dz1JsonStackData_new(Dz1JsonStackDataPresent_pair, NULL, errp)) == NULL) ERR_OUT(errp);
		else if ((d->x.pair = Dz1JsonStackPair_new(Dz1JsonStackPairState_init, p_spe, p_dst, errp)) == NULL) ERR_OUT(errp);
		else
		{
			_push_stk(psr, &nstk);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonStack_delAndSetNull, (void *)&nstk);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// static Dz1JsonStackArray *Dz1JsonStackArray_generate(Dz1JsonSpecArray *spa, Dz1JsonSpec *g_spec, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	Dz1JsonStackArray *ret = NULL;
// 	Dz1JsonSpecEntry *node_spe = Dz1JsonSpec_findType(g_spec, spa->elem_type);
// 	if (node_spe == NULL) ERR_SET_OUT(errp, ENOENT);	// check element type interface
// 	else if ((ret = Dz1JsonStackArray_new(Dz1JsonStackArrayState_init, errp)) == NULL) ERR_OUT(errp);
// 	else Dz1Error_set(errp, 0);
// 	return ret;
// }

Dz1JsonStackData *Dz1JsonStackData_gen_primitive(Dz1JsonSpecEntry *spe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStackData *ret = Dz1JsonStackData_new(Dz1JsonStackDataPresent_pr, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonStackData_delAndSetNull, (void *)&ret);
		if ((ret->x.pr = Dz1JsonStackPrimitive_new(Dz1JsonStackPrimitiveState_init, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonStackData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1JsonStackData *Dz1JsonStackData_gen_obj(Dz1JsonSpecEntry *spe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStackData *ret = Dz1JsonStackData_new(Dz1JsonStackDataPresent_obj, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonStackData_delAndSetNull, (void *)&ret);
		if ((ret->x.obj = Dz1JsonStackObj_new(errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1JsonStackData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

//Dz1JsonStackData *Dz1JsonStackData_generate(Dz1JsonSpecData *spd, Dz1JsonSpec *g_spec, Dz1Error *err)
Dz1JsonStackData *Dz1JsonStackData_generate(Dz1JsonSpecData *spd, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStackData *stk_data = NULL;
	if ((stk_data = Dz1JsonStackData_new(Dz1JsonStackDataPresent_max, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonStackData_delAndSetNull, (void *)&stk_data);
		switch(spd->present)
		{
		case Dz1JsonSpecDataPresent_pr:
			stk_data->present = Dz1JsonStackDataPresent_pr;
			if ((stk_data->x.pr = Dz1JsonStackPrimitive_new(Dz1JsonStackPrimitiveState_init, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_cst:
			stk_data->present = Dz1JsonStackDataPresent_st + spd->x.cst->type;
			if ((stk_data->x.st = Dz1JsonStackStruct_new(Dz1JsonStackStructState_init, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		case Dz1JsonSpecDataPresent_ar:
			stk_data->present = Dz1JsonStackDataPresent_ar;
//			if ((stk_data->x.ar = Dz1JsonStackArray_generate(spd->x.ar, g_spec, errp)) == NULL) ERR_OUT(errp);
			if ((stk_data->x.ar = Dz1JsonStackArray_new(Dz1JsonStackArrayState_init, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
		pthread_cleanup_pop(errp->code); // (Dz1JsonStackData_delAndSetNull, (void *)&stk_data);
	}
	return stk_data;
}

bool_t Dz1JsonEnv_stack_gen_push_pair(Dz1JsonEnv *psr, Dz1JsonVarBind *p_var, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecEntry *p_spe = p_var->type;
	if (p_var->data == NULL && p_spe->gen != NULL)
	{
		if ((p_var->data = p_spe->gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(_set_null, (void *)&p_var->data);
			pthread_cleanup_push((Dz1DelFunc)p_spe->del, p_var->data);

			if (Dz1JsonEnv_stack_pushPair(psr, p_spe, p_var->data, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // ((Dz1DelFunc)p_spe->del, p_var->data);
			pthread_cleanup_pop(errp->code); // (_set_null, (void *)&p_var->data);
		}
	}
	else
	{
		if (Dz1JsonEnv_stack_pushPair(psr, p_spe, p_var->data, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonEnv_stack_push(Dz1JsonEnv *psr, Dz1JsonSpecEntry *spe, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStack *nstk = Dz1JsonStack_new(NULL, NULL, errp);
	if (nstk == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonStack_delAndSetNull, (void *)&nstk);
		if ((nstk->dst_var = Dz1JsonVarBind_new(NULL, spe, NULL, errp)) == NULL) ERR_OUT(errp);
//		else if ((nstk->data = Dz1JsonStackData_generate(spe->data, psr->spec, errp)) == NULL) ERR_OUT(errp);
		else if ((nstk->data = Dz1JsonStackData_generate(spe->data, errp)) == NULL) ERR_OUT(errp);
		else
		{
			_push_stk(psr, &nstk);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonStack_delAndSetNull, (void *)&nstk);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1JsonEnv_stack_pop(Dz1JsonEnv *psr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonStack *stk = psr->stk;
	if (stk != NULL)
	{
		pthread_cleanup_push(Dz1JsonStack_delAndSetNull, (void *)&stk);

		psr->stk = stk->next;
		stk->next = NULL;

//		Dz1Thread_printf("<<< Return sub parser = "); Dz1JsonStack_dump(stk, 0);

		if (psr->stk == NULL)
		{
			Dz1JsonVarBind *result = stk->dst_var; 
			Dz1JsonSpecEntry *spe = result->type;
			Dz1JsonOutputEntry *node = Dz1JsonOutputEntry_new(NULL, result->data, spe->del, errp);
			if (node == NULL) ERR_OUT(errp);
			else
			{
				result->data = NULL;
				pthread_cleanup_push(Dz1JsonOutputEntry_delAndSetNull, (void *)&node);

				Dz1JsonOutputFifo_push(psr->egress, &node);
				node = NULL;
				Dz1Error_set(errp, 0);

				pthread_cleanup_pop(1); // (Dz1JsonOutputEntry_delAndSetNull, (void *)&node);
			}
		}
		else
		{
			Dz1JsonStack *caller_stk = psr->stk;
			caller_stk->ret_var = stk->dst_var;
			stk->dst_var = NULL;
		}
		pthread_cleanup_pop(1); // (Dz1JsonStack_delAndSetNull, (void *)&stk);
	}
	return errp->code == 0 ? TRUE : FALSE;
}


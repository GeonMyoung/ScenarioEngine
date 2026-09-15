#include <dz1_thread_stdio.h>
#include "Dz1JsonLexer.h"
#include "Dz1JsonStructUtil.h"
#include "Dz1JsonStack.h"
#include "Dz1JsonParsePair.h"

static bool_t _resolve_child(Dz1JsonVarBind *var, Dz1JsonStackPair *stk, Dz1Str name, Dz1JsonSpec *g_spec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonSpecConstruct *cstr = NULL;
	Dz1JsonSpecChild *child = NULL;

	Dz1JsonSpecEntry *p_spe = stk->par_type;
	Dz1JsonSpecData *p_spd = p_spe->data;
	switch(p_spd->present)
	{
	case Dz1JsonSpecDataPresent_cst:
		if ((cstr = p_spd->x.cst) == NULL) ERR_SET_OUT(errp, EFAULT);
		else if ((var->id = child = Dz1JsonSpecChilds_findByName(cstr->childs, name)) == NULL)
		{
			Dz1Thread_log(DZ1_THREAD_LOG_ERROR, ("_resolve_child() : Unknonw child = ")); Dz1Str_dump(name, 0);
			ERR_SET_OUT(errp, EPERM);
		}
		else if ((var->type = Dz1JsonSpec_findType(g_spec, child->type)) == NULL) ERR_SET_OUT(errp, EPERM);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EPERM);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static int Dz1Json_parsePairName(Dz1JsonEnv *psr, Dz1JsonVarBind *var, Dz1JsonStackPair *stk, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	Dz1JsonToken *token = NULL;
	if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
	{
		if (errp->code) ERR_OUT(errp);
		else ret = 0;
	}
	else
	{
		pthread_cleanup_push(_Dz1JsonLexer_consume, (void *)psr->lexer);

		if (token->t != Dz1JsonTokenType_string || token->v == NULL || token->v[0] == 0)
		{
			Dz1Thread_printf(Dz1T("!!! Invalid Token = ")); Dz1JsonToken_dump(token, 0);
			ERR_SET_OUT(errp, EPERM);
		}
		else if (_resolve_child(var, stk, token->v, psr->spec, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = 1;
		}

		pthread_cleanup_pop(1); // (_Dz1JsonLexer_consume, (void *)psr->lexer);
	}
	return ret;
}

static int Dz1Json_parsePairColon(Dz1JsonEnv *psr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	Dz1JsonToken *token = NULL;
	if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
	{
		if (errp->code) ERR_OUT(errp);
		else ret = 0;
	}
	else
	{
		pthread_cleanup_push(_Dz1JsonLexer_consume, (void *)psr->lexer);

		if (token->t != Dz1JsonTokenType_colon) ERR_SET_OUT(errp, EPERM);
		else
		{
			Dz1Error_set(errp, 0);
			ret = 1;
		}

		pthread_cleanup_pop(1); // (_Dz1JsonLexer_consume, (void *)psr->lexer);
	}
	return ret;
}

static bool_t _take_ret_val(Dz1JsonVarBind *own, Dz1JsonStack *stack, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonVarBind *ret_val = stack->ret_var;
	pthread_cleanup_push(Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
	if (own->data != NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		own->data = ret_val->data;
		ret_val->data = NULL;
		Dz1Error_set(errp, 0);
	}
	pthread_cleanup_pop(1); // (Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
	return errp->code == 0 ? TRUE : FALSE;
}

int Dz1Json_parsePair(Dz1JsonEnv *psr, Dz1JsonStack *stack, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	Dz1JsonVarBind *var = stack->dst_var;

	Dz1JsonStackData *stk_data = stack->data;	
	Dz1JsonStackPair *stk = stk_data->x.pair;
//	Dz1JsonSpecEntry *p_spe = stk->par_type;
//	void *p_obj = stk->par_ptr;

//	Dz1Thread_printf("Dz1Json_parsePair() state = "); Dz1JsonStackPairState_dump(&stk->state, 0);
	switch(stk->state)
	{
	default:
	case Dz1JsonStackPairState_parsing_name:
		stk->state = Dz1JsonStackPairState_parsing_name;
		if ((ret = Dz1Json_parsePairName(psr, var, stk, errp)) < 0) ERR_OUT(errp);
		else if (ret == 0) { }
		else
		{
			stk->state = Dz1JsonStackPairState_parsing_colon;
			Dz1Error_set(errp, 0);
			ret = 1;
		}
		break;
	case Dz1JsonStackPairState_parsing_colon:
		if ((ret = Dz1Json_parsePairColon(psr, errp)) < 0) ERR_OUT(errp);
		else if (ret == 0) { }
		else if (Dz1JsonEnv_stack_push(psr, var->type, errp) == FALSE) ERR_OUT(errp);
		else
		{
			stk->state = Dz1JsonStackPairState_parsing_object;
			Dz1Error_set(errp, 0);
			ret = 1;
		}
		break;
	case Dz1JsonStackPairState_parsing_object:
		if (_take_ret_val(var, stack, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = 1;
		}
		break;
	}
	return ret;
}


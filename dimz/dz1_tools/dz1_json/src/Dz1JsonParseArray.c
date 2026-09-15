#include <dz1_thread_stdio.h>
#include "Dz1JsonStructUtil.h"
#include "Dz1JsonLexer.h"
#include "Dz1JsonStack.h"
#include "Dz1JsonParseArray.h"

static bool_t _array_entry_push(Dz1JsonEnv *psr, Dz1JsonSpecEntry *spe, Dz1JsonStackArray *stk, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1JsonSpecData *spd = spe->data;
	Dz1JsonSpecArray *spa = spd->x.ar;

	Dz1JsonSpecEntry *elem_spe = NULL;

	if ((elem_spe = Dz1JsonSpec_findType(psr->spec, spa->elem_type)) == NULL) ERR_SET_OUT(errp, EFAULT);
	else if (Dz1JsonEnv_stack_push(psr, elem_spe, errp) == FALSE) ERR_OUT(errp);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _array_entry_add(Dz1JsonVarBind *own, Dz1JsonVarBind *node, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1JsonSpecEntry *own_spe = own->type;
	Dz1JsonSpecData *own_spd = own_spe->data;
	Dz1JsonSpecArray *own_spa = own_spd->x.ar;
	
	if (node->data != NULL && own_spa->append(own->data, node, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

int Dz1Json_parseArray(Dz1JsonEnv *psr, Dz1JsonStack *stack, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;

	Dz1JsonVarBind *var = stack->dst_var;
	Dz1JsonSpecEntry *spe = var->type;

	Dz1JsonStackData *stk_data = stack->data;
	Dz1JsonStackArray *stk = stk_data->x.ar;

	Dz1JsonToken *token = NULL;
//	Dz1Thread_printf("Dz1Json_parseArray() : %s\n", Dz1JsonStackArrayStateStr(stk->state));
	switch(stk->state)
	{
	default:
	case Dz1JsonStackArrayState_parsing_bstart:
		stk->state = Dz1JsonStackArrayState_parsing_bstart;
		if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
		{
			if (errp->code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 0;
			}
		}
		else if (token->t == Dz1JsonTokenType_blk_start)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (var->data == NULL && (var->data = spe->gen(errp)) == NULL) ERR_OUT(errp);
			else if (_array_entry_push(psr, spe, stk, errp) == FALSE) ERR_OUT(errp);
			else
			{
				stk->state = Dz1JsonStackArrayState_parsing_object;
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		else if (token->t == Dz1JsonTokenType_nul)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		break;
	case Dz1JsonStackArrayState_parsing_object:
		pthread_cleanup_push(Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
		if (_array_entry_add(var, stack->ret_var, errp) == FALSE) ERR_OUT(errp);
		else
		{
			stk->state = Dz1JsonStackArrayState_parsing_comma;
			Dz1Error_set(errp, 0);
			ret = 1;
		}
		pthread_cleanup_pop(1); // (Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
		break;
	case Dz1JsonStackArrayState_parsing_comma:
	case Dz1JsonStackArrayState_parsing_bend:
		if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
		{
			if (errp->code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 0;
			}
		}
		else if (token->t == Dz1JsonTokenType_comma)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (_array_entry_push(psr, spe, stk, errp) == FALSE) ERR_OUT(errp);
			else
			{
				stk->state = Dz1JsonStackArrayState_parsing_object;
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		else if (token->t == Dz1JsonTokenType_blk_end)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		else 
			ERR_SET_OUT(errp, EPERM);
		break;
	}
	return ret;
}


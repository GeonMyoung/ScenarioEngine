#include "Dz1JsonStructUtil.h"
#include "Dz1JsonLexer.h"
#include "Dz1JsonStack.h"
#include "Dz1JsonParseUnion.h"


int Dz1Json_parseUnion(Dz1JsonEnv *psr, Dz1JsonStack *stack, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1JsonStackData *stk_data = stack->data;
	Dz1JsonStackUnion *stk = stk_data->x.un;

	Dz1JsonVarBind *var = stack->dst_var;

	Dz1JsonToken *token = NULL;
	int ret = -1;
	switch(stk->state)
	{
	default:
	case Dz1JsonStackUnionState_parsing_lstart:
		stk->state = Dz1JsonStackUnionState_parsing_lstart;
		if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
		{
			if (errp->code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 0;
			}
		}
		else if (token->t == Dz1JsonTokenType_lst_start)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (Dz1JsonEnv_stack_gen_push_pair(psr, var, errp) == FALSE) ERR_OUT(errp);
			else
			{
				stk->state = Dz1JsonStackUnionState_parsing_pair;
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		else if (token->t == Dz1JsonTokenType_nul)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (var->data != NULL) ERR_SET_OUT(errp, EPERM);		// null일 수 없는 구조다
			else if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
			else
			{
				ret = 1;
				Dz1Error_set(errp, 0);
			}
		}
		break;
	case Dz1JsonStackUnionState_parsing_pair:
		pthread_cleanup_push(Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
		if (Dz1JsonConstruct_apply_child_data(var, stack->ret_var, errp) == FALSE) ERR_OUT(errp);
		else
		{
			stk->state = Dz1JsonStackUnionState_parsing_lend;
			ret = 1;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1JsonVarBind_delAndSetNull, (void *)&stack->ret_var);
		break;
	case Dz1JsonStackUnionState_parsing_lend:
		if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
		{
			if (errp->code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 0;
			}
		}
		else if (token->t == Dz1JsonTokenType_lst_end)
		{
			Dz1JsonLexer_consume(psr->lexer);
			if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				ret = 1;
			}
		}
		else ERR_SET_OUT(errp, EPERM);	// don't care condition
		break;
	}
	return ret;
}


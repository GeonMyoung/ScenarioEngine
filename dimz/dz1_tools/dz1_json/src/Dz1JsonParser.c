#include <dz1_thread_stdio.h>

#include "Dz1JsonStructUtil.h"
#include "Dz1JsonFifo.h"
#include "Dz1JsonLexer.h"
#include "Dz1JsonStack.h"
#include "Dz1JsonParseStruct.h"
#include "Dz1JsonParseUnion.h"
#include "Dz1JsonParseArray.h"
#include "Dz1JsonParsePair.h"
#include "Dz1JsonParseObj.h"
#include "Dz1JsonParser.h"

static bool_t Dz1Json_parsePrimitive_load(Dz1JsonVarBind *dst, Dz1JsonToken *token, Dz1Error *errp)
{
	bool_t ret = FALSE;

	Dz1JsonSpecEntry *spe = dst->type; 
	Dz1JsonSpecData *spd = spe->data;
	Dz1JsonSpecPrimitive *pr_spec = spd->x.pr;

	if (pr_spec->loader(dst, token, errp) == FALSE)  ERR_OUT(errp);
	else ret = TRUE;

	return ret;
}

static int Dz1Json_parsePrimitive(Dz1JsonEnv *psr, Dz1JsonStack *stack, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	int ret = -1;
	Dz1JsonToken *token = NULL;
	if ((token = Dz1JsonLexer_get(psr->lexer, psr->ingress, errp)) == NULL)
	{
		if (errp->code) ERR_OUT_RET(errp, -1);
		else ret = 0;
	}
	else if (token->v == NULL)
	{
		if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, EINVAL);
//			ret = 1;	// ???
			ret = -1;
		}
	}
	else
	{
		pthread_cleanup_push(_Dz1JsonLexer_consume, (void *)psr->lexer);

		if (Dz1Json_parsePrimitive_load(stack->dst_var, token, errp) == FALSE) ERR_OUT(errp);
		else if (Dz1JsonEnv_stack_pop(psr, errp) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Error_set(errp, 0);
			ret = 1;
		}
		pthread_cleanup_pop(1); // (_Dz1JsonLexer_consume, (void *)psr->lexer);

	}
	return ret;
}

int Dz1Json_parse(Dz1Json *h, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = -1;
	Dz1JsonEnv *psr = (Dz1JsonEnv *)h;
	if (psr == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		int status = -1;
		Dz1JsonStack *stk = NULL;
		Dz1JsonStackData *stk_data = NULL;

		do 
		{
			if ((stk = psr->stk) == NULL)
			{
				Dz1JsonSpecEntry *spe = psr->root_spe;
				if ((psr->stk = stk = Dz1JsonStack_new(NULL, NULL, errp)) == NULL) { ERR_OUT(errp); status = -1; break; }
				else if ((stk->dst_var = Dz1JsonVarBind_new(NULL, spe, NULL, errp)) == NULL) ERR_OUT(errp);
				else
				{
					Dz1JsonSpecData *spd = spe->data;
					if (spd->present == Dz1JsonSpecDataPresent_pr)
					{
						//if ((stk->data = Dz1JsonStackData_gen_obj(spe, errp)) == NULL) { ERR_OUT(errp); status = -1; break; }
						if ((stk->data = Dz1JsonStackData_gen_primitive(spe, errp)) == NULL) { ERR_OUT(errp); status = -1; break; }
						else Dz1Error_set(errp, 0);
					}
//					else if ((stk->data = Dz1JsonStackData_generate(spe->data, psr->spec, errp)) == NULL) { ERR_OUT(errp); status = -1; break; }
					else if ((stk->data = Dz1JsonStackData_generate(spe->data, errp)) == NULL) { ERR_OUT(errp); status = -1; break; }
					else Dz1Error_set(errp, 0);
				}
			}
			stk_data = stk->data;

			switch(stk_data->present)
			{
			case Dz1JsonStackDataPresent_pr:
				if ((status = Dz1Json_parsePrimitive(psr, stk, errp)) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1JsonStackDataPresent_st:
				if ((status = Dz1Json_parseStruct(psr, stk, errp)) < 0) 
					ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1JsonStackDataPresent_un:
				if ((status = Dz1Json_parseUnion(psr, stk, errp)) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1JsonStackDataPresent_ar:
				if ((status = Dz1Json_parseArray(psr, stk, errp)) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1JsonStackDataPresent_pair:
				if ((status = Dz1Json_parsePair(psr, stk, errp)) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			case Dz1JsonStackDataPresent_obj:
				if ((status = Dz1Json_parseObj(psr, stk, errp)) < 0) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
				break;
			default:
				ERR_SET_OUT(errp, EFAULT);
				status = -1;
				break;
			}
		} while(status > 0);

		if (status == 0)
		{
			if (Dz1JsonOutputFifo_isEmpty(psr->egress)) 
				ret = 0;
			else 
				ret = 1;
		}
		else
		{
			Dz1Thread_printf(Dz1T("JSON Status = ")); Dz1JsonEnv_dump(psr, 0);
		}
	}
	return ret;
}

#include <dz1_thread_stdio.h>
#include <Dz1Json.h>
#include "Dz1JsonFifo.h"
#include "Dz1JsonLexer.h"
#include "Dz1JsonStructUtil.h"

Dz1Json *Dz1Json_new(str_t remote_charset, Dz1JsonSpec *spec_ref, Dz1Str target, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonEnv *ret = Dz1JsonEnv_new(NULL, spec_ref, NULL, NULL, NULL, NULL, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1JsonEnv_delAndSetNull, (void *)&ret);

		if ((ret->lexer = Dz1JsonLexer_create(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->root_spe = Dz1JsonSpec_findType(ret->spec, target)) == NULL) ERR_SET_OUT(errp, EINVAL);
		else if ((ret->ingress = Dz1JsonFifo_create(remote_charset, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->egress = Dz1JsonOutputFifo_new(errp)) == NULL) ERR_OUT(errp);
		else if ((ret->stringify_conv = Dz1JsonConv_new(remote_charset, DZ1_SYSTEM_CHARSET, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->stringify_buf = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1JsonEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void Dz1Json_parserStack_clear(Dz1JsonEnv *env)
{
	while (env != NULL && env->stk != NULL)
	{
		Dz1JsonStack *stk = env->stk;

		env->stk = stk->next;
		stk->next = NULL;
		Dz1JsonStack_del(stk);
	}
}

void Dz1Json_del(Dz1Json *ptr)
{
	Dz1JsonEnv *p = (Dz1JsonEnv *)ptr;

	Dz1Json_parserStack_clear(p);
	Dz1JsonEnv_del(p);
}

ssize_t Dz1Json_push_stream(Dz1Json *h, u8_t *src, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t sz = 0;
	Dz1JsonEnv *psr = (Dz1JsonEnv *)h;
	if (psr == NULL || src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (size >0)
	{
		if ((sz = Dz1JsonFifo_ingress(psr->ingress, src, size, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return sz;
}

void *Dz1Json_read(Dz1Json *h, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	void *ret = NULL;

	Dz1JsonOutputEntry *node = NULL;
	Dz1JsonEnv *psr = (Dz1JsonEnv *)h;
	if (psr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((node = Dz1JsonOutputFifo_pop(psr->egress, errp)) == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
		else Dz1Error_set(errp, EAGAIN);
	}
	else
	{
		pthread_cleanup_push(Dz1JsonOutputEntry_delAndSetNull, (void *)&node);
		ret = node->result;
		node->result = NULL;
		pthread_cleanup_pop(1); // (Dz1JsonOutputEntry_delAndSetNull, (void *)&node);
	}
	return ret;
}

bool_t Dz1Json_setDebugFlagsLexer(Dz1Json *h, u32_t flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1JsonEnv *psr = (Dz1JsonEnv *)h;
	Dz1JsonLexer *lexer = NULL;
	if (psr == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((lexer = psr->lexer) == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		lexer->dbgs = flag;
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

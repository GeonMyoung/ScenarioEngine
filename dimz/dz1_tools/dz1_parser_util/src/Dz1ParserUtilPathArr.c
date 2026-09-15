#include "Dz1ParserUtil.h"

static Dz1Str *_parsePathStr(Dz1Str paths, u32_t *ret_cnt, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	u32_t cnt = 0;
	Dz1Str *ret = NULL;
	if (ret_cnt == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str), 64, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		if (Dz1Str_isVoid(paths) == FALSE)
		{
			TCHAR *cp = paths, buf[2048], *dp = buf;
			while(errp->code == 0 && *cp)
			{
				if (*cp == Dz1Text(';'))
				{	// end of string
					*dp++ = 0;
					dp = buf;

					if ((ret[cnt++] = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
				// normal letters
				else *dp++ = *cp;
				cp++;
			}

			if (errp->code == 0 )
			{
				if (dp > buf)
				{
					*dp++ = 0;
					if ((ret[cnt++] = Dz1Str_dup(buf, errp)) == NULL) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	*ret_cnt = cnt;
	return ret;
}

Dz1ParserUtilPathArr *Dz1ParserUtilPathArr_new(Dz1Str str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ParserUtilPathArr *ret = (Dz1ParserUtilPathArr *)Dz1Calloc(sizeof(Dz1ParserUtilPathArr), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ParserUtilPathArr_delAndSetNull, (void *)&ret);

		if ((ret->arr = _parsePathStr(str, &ret->cnt, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ParserUtilPathArr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1ParserUtilPathArr *Dz1ParserUtilPathArr_clone(Dz1ParserUtilPathArr *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ParserUtilPathArr *ret = (Dz1ParserUtilPathArr *)Dz1Calloc(sizeof(Dz1ParserUtilPathArr), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1ParserUtilPathArr_delAndSetNull, (void *)&ret);
		if ((ret->arr = (Dz1Str *)Dz1Calloc(sizeof(Dz1Str), (ret->cnt = src->cnt), errp)) == NULL) ERR_OUT(errp);
		else
		{
			u32_t i;
			for (i = 0; errp->code == 0 && i < src->cnt; i++)
			{
				if (src->arr[i] != NULL && (ret->arr[i] = Dz1Str_dup(src->arr[i], errp)) == NULL) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
		pthread_cleanup_pop(errp->code); // (Dz1ParserUtilPathArr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1ParserUtilPathArr_del(Dz1ParserUtilPathArr *p)
{
	if (p != NULL)
	{
		if (p->arr != NULL)
		{
			u32_t i;
			for (i = 0; i < p->cnt; i++)
			{
				if (p->arr[i] != NULL) 
					Dz1Str_delAndSetNull(&p->arr[i]);
			}
			Dz1Free(p->arr);
		}
		Dz1Free(p);
	}
}

void Dz1ParserUtilPathArr_dump(Dz1ParserUtilPathArr *p, int tab)
{
	if (p == NULL) Dz1Thread_printf("NULL\n");
	else if (p->cnt == 0) Dz1Thread_printf("Empty\n");
	else
	{
		u32_t i;
		for (i = 0; i < p->cnt; i++)
		{
			Dz1Thread_tprintf(tab, "include = ");
			Dz1Str_dump(p->arr[i], tab);
		}
	}
}

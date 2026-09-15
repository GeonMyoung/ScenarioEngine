#include "Dz1GifTypes.h"
#include <Dz1GifDef.h>

static Dz1Error _init_idx(void *ptr, Dz1GifColor *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1GifColorIndex *dst = (Dz1GifColorIndex *)ptr;
	if (p->idx > 255) ERR_SET_OUT(errp, EINVAL);
	else
	{
		dst->colors[p->idx] = p;
		dst->numOfColor++;
	}
	return err;
}

Dz1GifColorIndex *_Dz1GifColorIndex_new(Dz1GifColorList *src, Dz1Error *err, char *__file__, int __line__)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1GifColorIndex *ret = (Dz1GifColorIndex *)_Dz1Calloc(sizeof(Dz1GifColorIndex), 1, errp, __file__, __line__);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1GifColorIndex_delAndSetNull, (void *)&ret);
		if ((*errp = src->travel(src, _init_idx, (void *)ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1GifColorIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1GifColorIndex *Dz1GifColorIndex_clone(Dz1GifColorIndex *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1GifColorIndex *ret = (Dz1GifColorIndex *)Dz1Calloc(sizeof(Dz1GifColorIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else memcpy(ret, src, sizeof(Dz1GifColorIndex));
	return ret;
}

void Dz1GifColorIndex_del(Dz1GifColorIndex *p)
{
	if (p == NULL) return;
	Dz1Free(p);
}

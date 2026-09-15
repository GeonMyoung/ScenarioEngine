////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "Dz1GifDef.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataSubBlock
Dz1GifDataSubBlock *Dz1GifDataSubBlock_new(Dz1Binary *bin, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDataSubBlock *__internal_ret = (Dz1GifDataSubBlock *)Dz1Calloc(sizeof(Dz1GifDataSubBlock), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDataSubBlock_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->bin = bin;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDataSubBlock_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1GifDataSubBlock_dump(Dz1GifDataSubBlock *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("bin = ")); Dz1Binary_dump(p->bin, tab); 
		// Recursive member
		// Recursive but address dump
		Dz1Thread_tprintf(tab, Dz1T("next = %p\n"), p->next);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifDataSubBlock
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColor
Dz1GifColor *Dz1GifColor_new(u16_t idx, u8_t red, u8_t green, u8_t blue, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifColor *__internal_ret = (Dz1GifColor *)Dz1Calloc(sizeof(Dz1GifColor), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifColor_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->idx = idx;
		__internal_ret->red = red;
		__internal_ret->green = green;
		__internal_ret->blue = blue;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColor_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifColor_copy(Dz1GifColor *dst, Dz1GifColor *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->idx = src->idx;
		dst->red = src->red;
		dst->green = src->green;
		dst->blue = src->blue;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifColor *Dz1GifColor_clone(Dz1GifColor *src, Dz1Error *err)
{
	Dz1GifColor *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifColor *)Dz1Calloc(sizeof(Dz1GifColor), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifColor_delAndSetNull, (void *)&dst);
		if (Dz1GifColor_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColor_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifColor_purge(Dz1GifColor *p)
{
	if (p == NULL) return;
}

void Dz1GifColor_del(Dz1GifColor *p)
{
	if (p == NULL) return;
	Dz1GifColor_purge(p);
	Dz1Free(p);
}

int Dz1GifColor_cmp(Dz1GifColor *a, Dz1GifColor *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u16_cmp(&a->idx, &b->idx)) != 0) { }
	return ret;
}
// Dz1GifColor
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorList
static Dz1Error Dz1GifColorList_add(Dz1GifColorList *p, Dz1GifColor *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1AATree_find(p->storage, data)) ERR_SET_OUT(&err, EEXIST);
	else
	{
		err = Dz1AATree_insert(p->storage, data);
		if (ERR_PROBE(&err)) ERR_OUT(&err);
	}
	return err;
}

static bool_t Dz1GifColorList_remove(Dz1GifColorList *p, Dz1GifColor *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static Dz1GifColor *Dz1GifColorList_extract(Dz1GifColorList *p, Dz1GifColor *key)
{
	return (Dz1GifColor *)Dz1AATree_extract(p->storage, key);
}

typedef struct Dz1GifColorListMkArrArg
{
	Dz1GifColor **arr;
	unsigned int idx;
} Dz1GifColorListMkArrArg;

static Dz1Error _Dz1GifColorList_get_array(void *ptr, Dz1GifColor *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1GifColorListMkArrArg *arg = (Dz1GifColorListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1GifColor **Dz1GifColorList_get_array(Dz1GifColorList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1GifColor **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1GifColor **)Dz1Calloc(sizeof(Dz1GifColor *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1GifColorListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1GifColorList_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1GifColorList_travelForward(Dz1GifColorList *p, Dz1Error (*func)(void *ptr, Dz1GifColor *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error Dz1GifColorList_travelBackward(Dz1GifColorList *p, Dz1Error (*func)(void *ptr, Dz1GifColor *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1GifColor *Dz1GifColorList_find(Dz1GifColorList *p, Dz1GifColor *key)
{
	return (Dz1GifColor *)Dz1AATree_find(p->storage, key);
}

static Dz1GifColor *Dz1GifColorList_getHead(Dz1GifColorList *p)
{
	return (Dz1GifColor *)Dz1AATree_getHead(p->storage);
}

static unsigned int Dz1GifColorList_count(Dz1GifColorList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

Dz1GifColorList *Dz1GifColorList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifColorList *ret = (Dz1GifColorList *)Dz1Calloc(sizeof(Dz1GifColorList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1GifColorList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)Dz1GifColor_cmp,
				(Dz1DelFunc)Dz1GifColor_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1GifColorList_count;
			ret->travel = Dz1GifColorList_travelForward;
			ret->travelForward = Dz1GifColorList_travelForward;
			ret->travelBackward = Dz1GifColorList_travelBackward;
			ret->get_array = Dz1GifColorList_get_array;
			ret->add = Dz1GifColorList_add;
			ret->remove = Dz1GifColorList_remove;
			ret->find = Dz1GifColorList_find;
			ret->extract = Dz1GifColorList_extract;
			ret->getHead = Dz1GifColorList_getHead;
			ret->cmp = Dz1GifColor_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColorList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1GifColorList_clone(void *ptr, Dz1GifColor *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1GifColorList *p = (Dz1GifColorList *)ptr;
	Dz1GifColor *cloned = Dz1GifColor_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1GifColorList *Dz1GifColorList_clone(Dz1GifColorList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifColorList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1GifColorList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1GifColorList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_Dz1GifColorList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColorList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1GifColorList_purge(Dz1GifColorList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void Dz1GifColorList_del(Dz1GifColorList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1GifColorList_dump(void *ptr, Dz1GifColor *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1GifColor_dump(p, tab);
	return err;
}

void Dz1GifColorList_dump(Dz1GifColorList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1GifColorList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifColorList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifColorArray
Dz1GifColorArray *Dz1GifColorArray_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifColorArray *__internal_ret = (Dz1GifColorArray *)Dz1Calloc(sizeof(Dz1GifColorArray), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifColorArray_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->list = Dz1GifColorList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColorArray_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifColorArray_copy(Dz1GifColorArray *dst, Dz1GifColorArray *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->list && (dst->list = Dz1GifColorList_clone(src->list, errp)) == NULL) ERR_OUT(errp);
	else if (src->idx && (dst->idx = Dz1GifColorIndex_clone(src->idx, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifColorArray *Dz1GifColorArray_clone(Dz1GifColorArray *src, Dz1Error *err)
{
	Dz1GifColorArray *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifColorArray *)Dz1Calloc(sizeof(Dz1GifColorArray), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifColorArray_delAndSetNull, (void *)&dst);
		if (Dz1GifColorArray_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifColorArray_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifColorArray_purge(Dz1GifColorArray *p)
{
	if (p == NULL) return;
	Dz1GifColorList_del(p->list);
	Dz1GifColorIndex_del(p->idx);
}

void Dz1GifColorArray_del(Dz1GifColorArray *p)
{
	if (p == NULL) return;
	Dz1GifColorArray_purge(p);
	Dz1Free(p);
}

void Dz1GifColorArray_dump(Dz1GifColorArray *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("list = ")); Dz1GifColorList_dump(p->list, tab); 
	}
}
// Dz1GifColorArray
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifHeader
Dz1GifHeader *Dz1GifHeader_new(str_t sig, str_t ver, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifHeader *__internal_ret = (Dz1GifHeader *)Dz1Calloc(sizeof(Dz1GifHeader), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifHeader_delAndSetNull, (void *)&__internal_ret);
		
		if (sig && (__internal_ret->sig = dz1_built_in_str_clone(sig, errp)) == NULL) ERR_OUT(errp);
		else if (ver && (__internal_ret->ver = dz1_built_in_str_clone(ver, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifHeader_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifHeader_copy(Dz1GifHeader *dst, Dz1GifHeader *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->sig && (dst->sig = dz1_built_in_str_clone(src->sig, errp)) == NULL) ERR_OUT(errp);
	else if (src->ver && (dst->ver = dz1_built_in_str_clone(src->ver, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifHeader *Dz1GifHeader_clone(Dz1GifHeader *src, Dz1Error *err)
{
	Dz1GifHeader *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifHeader *)Dz1Calloc(sizeof(Dz1GifHeader), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifHeader_delAndSetNull, (void *)&dst);
		if (Dz1GifHeader_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifHeader_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifHeader_purge(Dz1GifHeader *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->sig);
	dz1_built_in_str_del(p->ver);
}

void Dz1GifHeader_del(Dz1GifHeader *p)
{
	if (p == NULL) return;
	Dz1GifHeader_purge(p);
	Dz1Free(p);
}

void Dz1GifHeader_dump(Dz1GifHeader *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("sig = ")); dz1_built_in_str_dump(p->sig, tab); 
		Dz1Thread_tprintf(tab, Dz1T("ver = ")); dz1_built_in_str_dump(p->ver, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifHeader
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDescr
Dz1GifDescr *Dz1GifDescr_new(u16_t width, 
							 u16_t height, 
							 bool_t gctPresent, 
							 s8_t color_res, 
							 bool_t gctIsSorted, 
							 s8_t gctSizeExp, 
							 u8_t bgcIdx, 
							 u8_t aspect, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDescr *__internal_ret = (Dz1GifDescr *)Dz1Calloc(sizeof(Dz1GifDescr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDescr_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->width = width;
		__internal_ret->height = height;
		__internal_ret->gctPresent = gctPresent;
		__internal_ret->color_res = color_res;
		__internal_ret->gctIsSorted = gctIsSorted;
		__internal_ret->gctSizeExp = gctSizeExp;
		__internal_ret->bgcIdx = bgcIdx;
		__internal_ret->aspect = aspect;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDescr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifDescr_copy(Dz1GifDescr *dst, Dz1GifDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->palette && (dst->palette = Dz1GifColorArray_clone(src->palette, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->width = src->width;
		dst->height = src->height;
		dst->gctPresent = src->gctPresent;
		dst->color_res = src->color_res;
		dst->gctIsSorted = src->gctIsSorted;
		dst->gctSizeExp = src->gctSizeExp;
		dst->bgcIdx = src->bgcIdx;
		dst->aspect = src->aspect;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifDescr *Dz1GifDescr_clone(Dz1GifDescr *src, Dz1Error *err)
{
	Dz1GifDescr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifDescr *)Dz1Calloc(sizeof(Dz1GifDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifDescr_delAndSetNull, (void *)&dst);
		if (Dz1GifDescr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDescr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifDescr_purge(Dz1GifDescr *p)
{
	if (p == NULL) return;
	Dz1GifColorArray_del(p->palette);
}

void Dz1GifDescr_del(Dz1GifDescr *p)
{
	if (p == NULL) return;
	Dz1GifDescr_purge(p);
	Dz1Free(p);
}

void Dz1GifDescr_dump(Dz1GifDescr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("width = ")); Dz1u16_dump(&p->width, tab); 
		Dz1Thread_tprintf(tab, Dz1T("height = ")); Dz1u16_dump(&p->height, tab); 
		Dz1Thread_tprintf(tab, Dz1T("gctPresent = ")); Dz1Bool_dump(&p->gctPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("color_res = ")); Dz1s8_dump(&p->color_res, tab); 
		Dz1Thread_tprintf(tab, Dz1T("gctIsSorted = ")); Dz1Bool_dump(&p->gctIsSorted, tab); 
		Dz1Thread_tprintf(tab, Dz1T("gctSizeExp = ")); Dz1s8_dump(&p->gctSizeExp, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bgcIdx = ")); Dz1u8_dump(&p->bgcIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("aspect = ")); Dz1u8_dump(&p->aspect, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("palette = ")); Dz1GifColorArray_dump(p->palette, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifImgDescr
Dz1GifImgDescr *Dz1GifImgDescr_new(u32_t x, 
								   u32_t y, 
								   u32_t width, 
								   u32_t height, 
								   bool_t lctPresent, 
								   bool_t isInterlaced, 
								   bool_t lctIsSorted, 
								   s8_t lctSizeExp, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifImgDescr *__internal_ret = (Dz1GifImgDescr *)Dz1Calloc(sizeof(Dz1GifImgDescr), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifImgDescr_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->x = x;
		__internal_ret->y = y;
		__internal_ret->width = width;
		__internal_ret->height = height;
		__internal_ret->lctPresent = lctPresent;
		__internal_ret->isInterlaced = isInterlaced;
		__internal_ret->lctIsSorted = lctIsSorted;
		__internal_ret->lctSizeExp = lctSizeExp;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifImgDescr_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifImgDescr_copy(Dz1GifImgDescr *dst, Dz1GifImgDescr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->palette && (dst->palette = Dz1GifColorArray_clone(src->palette, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->x = src->x;
		dst->y = src->y;
		dst->width = src->width;
		dst->height = src->height;
		dst->lctPresent = src->lctPresent;
		dst->isInterlaced = src->isInterlaced;
		dst->lctIsSorted = src->lctIsSorted;
		dst->lctSizeExp = src->lctSizeExp;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifImgDescr *Dz1GifImgDescr_clone(Dz1GifImgDescr *src, Dz1Error *err)
{
	Dz1GifImgDescr *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifImgDescr *)Dz1Calloc(sizeof(Dz1GifImgDescr), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifImgDescr_delAndSetNull, (void *)&dst);
		if (Dz1GifImgDescr_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifImgDescr_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifImgDescr_purge(Dz1GifImgDescr *p)
{
	if (p == NULL) return;
	Dz1GifColorArray_del(p->palette);
}

void Dz1GifImgDescr_del(Dz1GifImgDescr *p)
{
	if (p == NULL) return;
	Dz1GifImgDescr_purge(p);
	Dz1Free(p);
}

// Dz1GifImgDescr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlCmd
static struct Dz1GifGraphicControlCmdMapA
{
	str_t str;
	Dz1GifGraphicControlCmd v;
} Dz1GifGraphicControlCmdMapA[] =
{
	{ (char *)"noMean", Dz1GifGraphicControlCmd_noMean },
	{ (char *)"doNotDispose", Dz1GifGraphicControlCmd_doNotDispose },
	{ (char *)"restoreToBgColor", Dz1GifGraphicControlCmd_restoreToBgColor },
	{ (char *)"restoreToPrev", Dz1GifGraphicControlCmd_restoreToPrev },
	{ NULL, Dz1GifGraphicControlCmd_max }
};

str_t Dz1GifGraphicControlCmdStrA(Dz1GifGraphicControlCmd v)
{
	struct Dz1GifGraphicControlCmdMapA *i = NULL;
	for (i = Dz1GifGraphicControlCmdMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifGraphicControlCmd Dz1GifGraphicControlCmdFromStrA(str_t str)
{
	struct Dz1GifGraphicControlCmdMapA *i = NULL;
	for (i = Dz1GifGraphicControlCmdMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GifGraphicControlCmd_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GifGraphicControlCmdMapW
{
	wstr_t str;
	Dz1GifGraphicControlCmd v;
} Dz1GifGraphicControlCmdMapW[] =
{
	{ (wchar_t *)L"noMean", Dz1GifGraphicControlCmd_noMean },
	{ (wchar_t *)L"doNotDispose", Dz1GifGraphicControlCmd_doNotDispose },
	{ (wchar_t *)L"restoreToBgColor", Dz1GifGraphicControlCmd_restoreToBgColor },
	{ (wchar_t *)L"restoreToPrev", Dz1GifGraphicControlCmd_restoreToPrev },
	{ NULL, Dz1GifGraphicControlCmd_max }
};

wstr_t Dz1GifGraphicControlCmdStrW(Dz1GifGraphicControlCmd v)
{
	struct Dz1GifGraphicControlCmdMapW *i = NULL;
	for (i = Dz1GifGraphicControlCmdMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifGraphicControlCmd Dz1GifGraphicControlCmdFromStrW(wstr_t str)
{
	struct Dz1GifGraphicControlCmdMapW *i = NULL;
	for (i = Dz1GifGraphicControlCmdMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GifGraphicControlCmd_max;
}
#endif // UNIX_SYSTEM

Dz1GifGraphicControlCmd *Dz1GifGraphicControlCmd_new(Dz1GifGraphicControlCmd *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifGraphicControlCmd *__internal_ret = (Dz1GifGraphicControlCmd *)Dz1Calloc(sizeof(Dz1GifGraphicControlCmd), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1GifGraphicControlCmd
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphicControlExt
Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_new(Dz1GifGraphicControlCmd disposal, 
													 bool_t userInput, 
													 bool_t tpColPresent, 
													 u16_t delay, 
													 u8_t tpColorIdx, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifGraphicControlExt *__internal_ret = (Dz1GifGraphicControlExt *)Dz1Calloc(sizeof(Dz1GifGraphicControlExt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifGraphicControlExt_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->disposal = disposal;
		__internal_ret->userInput = userInput;
		__internal_ret->tpColPresent = tpColPresent;
		__internal_ret->delay = delay;
		__internal_ret->tpColorIdx = tpColorIdx;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifGraphicControlExt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifGraphicControlExt_copy(Dz1GifGraphicControlExt *dst, Dz1GifGraphicControlExt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else
	{
		dst->disposal = src->disposal;
		dst->userInput = src->userInput;
		dst->tpColPresent = src->tpColPresent;
		dst->delay = src->delay;
		dst->tpColorIdx = src->tpColorIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifGraphicControlExt *Dz1GifGraphicControlExt_clone(Dz1GifGraphicControlExt *src, Dz1Error *err)
{
	Dz1GifGraphicControlExt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifGraphicControlExt *)Dz1Calloc(sizeof(Dz1GifGraphicControlExt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifGraphicControlExt_delAndSetNull, (void *)&dst);
		if (Dz1GifGraphicControlExt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifGraphicControlExt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifGraphicControlExt_purge(Dz1GifGraphicControlExt *p)
{
	if (p == NULL) return;
}

void Dz1GifGraphicControlExt_del(Dz1GifGraphicControlExt *p)
{
	if (p == NULL) return;
	Dz1GifGraphicControlExt_purge(p);
	Dz1Free(p);
}

void Dz1GifGraphicControlExt_dump(Dz1GifGraphicControlExt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("disposal = %s(%d)\n"), Dz1GifGraphicControlCmdStr(p->disposal), p->disposal);
		Dz1Thread_tprintf(tab, Dz1T("userInput = ")); Dz1Bool_dump(&p->userInput, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tpColPresent = ")); Dz1Bool_dump(&p->tpColPresent, tab); 
		Dz1Thread_tprintf(tab, Dz1T("delay = ")); Dz1u16_dump(&p->delay, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tpColorIdx = ")); Dz1u8_dump(&p->tpColorIdx, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifGraphicControlExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifCommentExt
Dz1GifCommentExt *Dz1GifCommentExt_new(str_t text, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifCommentExt *__internal_ret = (Dz1GifCommentExt *)Dz1Calloc(sizeof(Dz1GifCommentExt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifCommentExt_delAndSetNull, (void *)&__internal_ret);
		
		if (text && (__internal_ret->text = dz1_built_in_str_clone(text, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifCommentExt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifCommentExt_copy(Dz1GifCommentExt *dst, Dz1GifCommentExt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->text && (dst->text = dz1_built_in_str_clone(src->text, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifCommentExt *Dz1GifCommentExt_clone(Dz1GifCommentExt *src, Dz1Error *err)
{
	Dz1GifCommentExt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifCommentExt *)Dz1Calloc(sizeof(Dz1GifCommentExt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifCommentExt_delAndSetNull, (void *)&dst);
		if (Dz1GifCommentExt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifCommentExt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifCommentExt_purge(Dz1GifCommentExt *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->text);
}

void Dz1GifCommentExt_del(Dz1GifCommentExt *p)
{
	if (p == NULL) return;
	Dz1GifCommentExt_purge(p);
	Dz1Free(p);
}

void Dz1GifCommentExt_dump(Dz1GifCommentExt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("text = ")); dz1_built_in_str_dump(p->text, tab); 
	}
}
// Dz1GifCommentExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifAppExt
Dz1GifAppExt *Dz1GifAppExt_new(str_t app, 
							   Dz1Binary *app_auth, 
							   Dz1Binary *app_data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifAppExt *__internal_ret = (Dz1GifAppExt *)Dz1Calloc(sizeof(Dz1GifAppExt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifAppExt_delAndSetNull, (void *)&__internal_ret);
		
		if (app && (__internal_ret->app = dz1_built_in_str_clone(app, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->app_auth = app_auth;
			__internal_ret->app_data = app_data;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifAppExt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifAppExt_copy(Dz1GifAppExt *dst, Dz1GifAppExt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->app && (dst->app = dz1_built_in_str_clone(src->app, errp)) == NULL) ERR_OUT(errp);
	else if (src->app_auth && (dst->app_auth = Dz1Binary_clone(src->app_auth, errp)) == NULL) ERR_OUT(errp);
	else if (src->app_data && (dst->app_data = Dz1Binary_clone(src->app_data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifAppExt *Dz1GifAppExt_clone(Dz1GifAppExt *src, Dz1Error *err)
{
	Dz1GifAppExt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifAppExt *)Dz1Calloc(sizeof(Dz1GifAppExt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifAppExt_delAndSetNull, (void *)&dst);
		if (Dz1GifAppExt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifAppExt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifAppExt_purge(Dz1GifAppExt *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->app);
	Dz1Binary_del(p->app_auth);
	Dz1Binary_del(p->app_data);
}

void Dz1GifAppExt_del(Dz1GifAppExt *p)
{
	if (p == NULL) return;
	Dz1GifAppExt_purge(p);
	Dz1Free(p);
}

void Dz1GifAppExt_dump(Dz1GifAppExt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("app = ")); dz1_built_in_str_dump(p->app, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("app_auth = ")); Dz1Binary_dump(p->app_auth, tab); 
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("app_data = ")); Dz1Binary_dump(p->app_data, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifAppExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderPlainTextExt
Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_new(u16_t x, 
													   u16_t y, 
													   u16_t width, 
													   u16_t height, 
													   u8_t cellWidth, 
													   u8_t cellHeight, 
													   u8_t fgColorIdx, 
													   u8_t bgColorIdx, 
													   str_t text, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifRenderPlainTextExt *__internal_ret = (Dz1GifRenderPlainTextExt *)Dz1Calloc(sizeof(Dz1GifRenderPlainTextExt), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderPlainTextExt_delAndSetNull, (void *)&__internal_ret);
		
		if (text && (__internal_ret->text = dz1_built_in_str_clone(text, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->x = x;
			__internal_ret->y = y;
			__internal_ret->width = width;
			__internal_ret->height = height;
			__internal_ret->cellWidth = cellWidth;
			__internal_ret->cellHeight = cellHeight;
			__internal_ret->fgColorIdx = fgColorIdx;
			__internal_ret->bgColorIdx = bgColorIdx;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderPlainTextExt_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifRenderPlainTextExt_copy(Dz1GifRenderPlainTextExt *dst, Dz1GifRenderPlainTextExt *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->text && (dst->text = dz1_built_in_str_clone(src->text, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->x = src->x;
		dst->y = src->y;
		dst->width = src->width;
		dst->height = src->height;
		dst->cellWidth = src->cellWidth;
		dst->cellHeight = src->cellHeight;
		dst->fgColorIdx = src->fgColorIdx;
		dst->bgColorIdx = src->bgColorIdx;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifRenderPlainTextExt *Dz1GifRenderPlainTextExt_clone(Dz1GifRenderPlainTextExt *src, Dz1Error *err)
{
	Dz1GifRenderPlainTextExt *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifRenderPlainTextExt *)Dz1Calloc(sizeof(Dz1GifRenderPlainTextExt), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderPlainTextExt_delAndSetNull, (void *)&dst);
		if (Dz1GifRenderPlainTextExt_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderPlainTextExt_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifRenderPlainTextExt_purge(Dz1GifRenderPlainTextExt *p)
{
	if (p == NULL) return;
	dz1_built_in_str_del(p->text);
}

void Dz1GifRenderPlainTextExt_del(Dz1GifRenderPlainTextExt *p)
{
	if (p == NULL) return;
	Dz1GifRenderPlainTextExt_purge(p);
	Dz1Free(p);
}

void Dz1GifRenderPlainTextExt_dump(Dz1GifRenderPlainTextExt *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("x = ")); Dz1u16_dump(&p->x, tab); 
		Dz1Thread_tprintf(tab, Dz1T("y = ")); Dz1u16_dump(&p->y, tab); 
		Dz1Thread_tprintf(tab, Dz1T("width = ")); Dz1u16_dump(&p->width, tab); 
		Dz1Thread_tprintf(tab, Dz1T("height = ")); Dz1u16_dump(&p->height, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cellWidth = ")); Dz1u8_dump(&p->cellWidth, tab); 
		Dz1Thread_tprintf(tab, Dz1T("cellHeight = ")); Dz1u8_dump(&p->cellHeight, tab); 
		Dz1Thread_tprintf(tab, Dz1T("fgColorIdx = ")); Dz1u8_dump(&p->fgColorIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("bgColorIdx = ")); Dz1u8_dump(&p->bgColorIdx, tab); 
		Dz1Thread_tprintf(tab, Dz1T("text = ")); dz1_built_in_str_dump(p->text, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifRenderPlainTextExt
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifTableBasedImgData
Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_new(u8_t lzwMinimumCodeSize, 
													 Dz1Binary *lzw, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifTableBasedImgData *__internal_ret = (Dz1GifTableBasedImgData *)Dz1Calloc(sizeof(Dz1GifTableBasedImgData), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifTableBasedImgData_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->lzwMinimumCodeSize = lzwMinimumCodeSize;
		__internal_ret->lzw = lzw;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifTableBasedImgData_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifTableBasedImgData_copy(Dz1GifTableBasedImgData *dst, Dz1GifTableBasedImgData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->lzw && (dst->lzw = Dz1Binary_clone(src->lzw, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->lzwMinimumCodeSize = src->lzwMinimumCodeSize;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifTableBasedImgData *Dz1GifTableBasedImgData_clone(Dz1GifTableBasedImgData *src, Dz1Error *err)
{
	Dz1GifTableBasedImgData *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifTableBasedImgData *)Dz1Calloc(sizeof(Dz1GifTableBasedImgData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifTableBasedImgData_delAndSetNull, (void *)&dst);
		if (Dz1GifTableBasedImgData_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifTableBasedImgData_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifTableBasedImgData_purge(Dz1GifTableBasedImgData *p)
{
	if (p == NULL) return;
	Dz1Binary_del(p->lzw);
}

void Dz1GifTableBasedImgData_del(Dz1GifTableBasedImgData *p)
{
	if (p == NULL) return;
	Dz1GifTableBasedImgData_purge(p);
	Dz1Free(p);
}

// Dz1GifTableBasedImgData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderTableBasedImg
Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_new(Dz1GifImgDescr *descr, 
														 Dz1Binary *pixels, 
														 Dz1GifTableBasedImgData *lzw, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifRenderTableBasedImg *__internal_ret = (Dz1GifRenderTableBasedImg *)Dz1Calloc(sizeof(Dz1GifRenderTableBasedImg), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderTableBasedImg_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->descr = descr;
		__internal_ret->pixels = pixels;
		__internal_ret->lzw = lzw;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderTableBasedImg_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifRenderTableBasedImg_copy(Dz1GifRenderTableBasedImg *dst, Dz1GifRenderTableBasedImg *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->descr && (dst->descr = Dz1GifImgDescr_clone(src->descr, errp)) == NULL) ERR_OUT(errp);
	else if (src->pixels && (dst->pixels = Dz1Binary_clone(src->pixels, errp)) == NULL) ERR_OUT(errp);
	else if (src->lzw && (dst->lzw = Dz1GifTableBasedImgData_clone(src->lzw, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifRenderTableBasedImg *Dz1GifRenderTableBasedImg_clone(Dz1GifRenderTableBasedImg *src, Dz1Error *err)
{
	Dz1GifRenderTableBasedImg *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifRenderTableBasedImg *)Dz1Calloc(sizeof(Dz1GifRenderTableBasedImg), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderTableBasedImg_delAndSetNull, (void *)&dst);
		if (Dz1GifRenderTableBasedImg_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderTableBasedImg_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifRenderTableBasedImg_purge(Dz1GifRenderTableBasedImg *p)
{
	if (p == NULL) return;
	Dz1GifImgDescr_del(p->descr);
	Dz1Binary_del(p->pixels);
	Dz1GifTableBasedImgData_del(p->lzw);
}

void Dz1GifRenderTableBasedImg_del(Dz1GifRenderTableBasedImg *p)
{
	if (p == NULL) return;
	Dz1GifRenderTableBasedImg_purge(p);
	Dz1Free(p);
}

// Dz1GifRenderTableBasedImg
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingDataPresent
static struct Dz1GifRenderingDataPresentMapA
{
	str_t str;
	Dz1GifRenderingDataPresent v;
} Dz1GifRenderingDataPresentMapA[] =
{
	{ (char *)"tbi", Dz1GifRenderingDataPresent_tbi },
	{ (char *)"pte", Dz1GifRenderingDataPresent_pte },
	{ NULL, Dz1GifRenderingDataPresent_max }
};

str_t Dz1GifRenderingDataPresentStrA(Dz1GifRenderingDataPresent v)
{
	struct Dz1GifRenderingDataPresentMapA *i = NULL;
	for (i = Dz1GifRenderingDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifRenderingDataPresent Dz1GifRenderingDataPresentFromStrA(str_t str)
{
	struct Dz1GifRenderingDataPresentMapA *i = NULL;
	for (i = Dz1GifRenderingDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GifRenderingDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GifRenderingDataPresentMapW
{
	wstr_t str;
	Dz1GifRenderingDataPresent v;
} Dz1GifRenderingDataPresentMapW[] =
{
	{ (wchar_t *)L"tbi", Dz1GifRenderingDataPresent_tbi },
	{ (wchar_t *)L"pte", Dz1GifRenderingDataPresent_pte },
	{ NULL, Dz1GifRenderingDataPresent_max }
};

wstr_t Dz1GifRenderingDataPresentStrW(Dz1GifRenderingDataPresent v)
{
	struct Dz1GifRenderingDataPresentMapW *i = NULL;
	for (i = Dz1GifRenderingDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifRenderingDataPresent Dz1GifRenderingDataPresentFromStrW(wstr_t str)
{
	struct Dz1GifRenderingDataPresentMapW *i = NULL;
	for (i = Dz1GifRenderingDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GifRenderingDataPresent_max;
}
#endif // UNIX_SYSTEM

Dz1GifRenderingDataPresent *Dz1GifRenderingDataPresent_new(Dz1GifRenderingDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifRenderingDataPresent *__internal_ret = (Dz1GifRenderingDataPresent *)Dz1Calloc(sizeof(Dz1GifRenderingDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1GifRenderingDataPresent_dump(Dz1GifRenderingDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1GifRenderingDataPresentStr(*v));
}
// Dz1GifRenderingDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifRenderingData
Dz1GifRenderingData *Dz1GifRenderingData_new(Dz1GifRenderingDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifRenderingData *ret = (Dz1GifRenderingData *)Dz1Calloc(sizeof(Dz1GifRenderingData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderingData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1GifRenderingDataPresent_tbi:
			// _U_cst_clone
			if (ptr != NULL) ret->x.tbi = (Dz1GifRenderTableBasedImg *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifRenderingDataPresent_pte:
			// _U_cst_clone
			if (ptr != NULL) ret->x.pte = (Dz1GifRenderPlainTextExt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifRenderingDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderingData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1GifRenderingData_copy(Dz1GifRenderingData *ret, Dz1GifRenderingData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1GifRenderingDataPresent_tbi:
			// _U_cst_clone
			if (src->x.tbi && (ret->x.tbi = Dz1GifRenderTableBasedImg_clone(src->x.tbi, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1GifRenderingDataPresent_pte:
			// _U_cst_clone
			if (src->x.pte && (ret->x.pte = Dz1GifRenderPlainTextExt_clone(src->x.pte, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifRenderingData *Dz1GifRenderingData_clone(Dz1GifRenderingData *src, Dz1Error *err)
{
	Dz1GifRenderingData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1GifRenderingData *)Dz1Calloc(sizeof(Dz1GifRenderingData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifRenderingData_delAndSetNull, (void *)&ret);
		if (Dz1GifRenderingData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifRenderingData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1GifRenderingData_purge(Dz1GifRenderingData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1GifRenderingDataPresent_tbi:
		Dz1GifRenderTableBasedImg_del(p->x.tbi);
		break;
	case Dz1GifRenderingDataPresent_pte:
		Dz1GifRenderPlainTextExt_del(p->x.pte);
		break;
	default:
		break;
	}
}

void Dz1GifRenderingData_del(Dz1GifRenderingData *p)
{
	if (!p) return;
	Dz1GifRenderingData_purge(p);
	Dz1Free(p);
}

void Dz1GifRenderingData_dump(Dz1GifRenderingData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1GifRenderingDataPresent_tbi:
		Dz1Thread_printf(Dz1T("tbi = ")); Dz1GifRenderTableBasedImg_dump(p->x.tbi, tab); 
		break;
	case Dz1GifRenderingDataPresent_pte:
		Dz1Thread_printf(Dz1T("pte = ")); Dz1GifRenderPlainTextExt_dump(p->x.pte, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1GifRenderingData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifGraphic
Dz1GifGraphic *Dz1GifGraphic_new(Dz1GifGraphicControlExt *gce, 
								 Dz1GifRenderingData *data, 
								 u32_t thid, 
								 bool_t isDone, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifGraphic *__internal_ret = (Dz1GifGraphic *)Dz1Calloc(sizeof(Dz1GifGraphic), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifGraphic_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->gce = gce;
		__internal_ret->data = data;
		__internal_ret->thid = thid;
		__internal_ret->isDone = isDone;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifGraphic_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1GifGraphic_copy(Dz1GifGraphic *dst, Dz1GifGraphic *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->gce && (dst->gce = Dz1GifGraphicControlExt_clone(src->gce, errp)) == NULL) ERR_OUT(errp);
	else if (src->data && (dst->data = Dz1GifRenderingData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->thid = src->thid;
		dst->isDone = src->isDone;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifGraphic *Dz1GifGraphic_clone(Dz1GifGraphic *src, Dz1Error *err)
{
	Dz1GifGraphic *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1GifGraphic *)Dz1Calloc(sizeof(Dz1GifGraphic), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifGraphic_delAndSetNull, (void *)&dst);
		if (Dz1GifGraphic_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifGraphic_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1GifGraphic_purge(Dz1GifGraphic *p)
{
	if (p == NULL) return;
	Dz1GifGraphicControlExt_del(p->gce);
	Dz1GifRenderingData_del(p->data);
}

void Dz1GifGraphic_del(Dz1GifGraphic *p)
{
	if (p == NULL) return;
	Dz1GifGraphic_purge(p);
	Dz1Free(p);
}

void Dz1GifGraphic_dump(Dz1GifGraphic *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("gce = ")); Dz1GifGraphicControlExt_dump(p->gce, tab); 
		Dz1Thread_tprintf(tab, Dz1T("data.")); Dz1GifRenderingData_dump(p->data, tab); 
		Dz1Thread_tprintf(tab, Dz1T("thid = ")); Dz1u32_dump(&p->thid, tab); 
		Dz1Thread_tprintf(tab, Dz1T("isDone = ")); Dz1Bool_dump(&p->isDone, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifGraphic
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntryPresent
static struct Dz1GifDataEntryPresentMapA
{
	str_t str;
	Dz1GifDataEntryPresent v;
} Dz1GifDataEntryPresentMapA[] =
{
	{ (char *)"graphic", Dz1GifDataEntryPresent_graphic },
	{ (char *)"app_ext", Dz1GifDataEntryPresent_app_ext },
	{ (char *)"comment", Dz1GifDataEntryPresent_comment },
	{ NULL, Dz1GifDataEntryPresent_max }
};

str_t Dz1GifDataEntryPresentStrA(Dz1GifDataEntryPresent v)
{
	struct Dz1GifDataEntryPresentMapA *i = NULL;
	for (i = Dz1GifDataEntryPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifDataEntryPresent Dz1GifDataEntryPresentFromStrA(str_t str)
{
	struct Dz1GifDataEntryPresentMapA *i = NULL;
	for (i = Dz1GifDataEntryPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GifDataEntryPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GifDataEntryPresentMapW
{
	wstr_t str;
	Dz1GifDataEntryPresent v;
} Dz1GifDataEntryPresentMapW[] =
{
	{ (wchar_t *)L"graphic", Dz1GifDataEntryPresent_graphic },
	{ (wchar_t *)L"app_ext", Dz1GifDataEntryPresent_app_ext },
	{ (wchar_t *)L"comment", Dz1GifDataEntryPresent_comment },
	{ NULL, Dz1GifDataEntryPresent_max }
};

wstr_t Dz1GifDataEntryPresentStrW(Dz1GifDataEntryPresent v)
{
	struct Dz1GifDataEntryPresentMapW *i = NULL;
	for (i = Dz1GifDataEntryPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifDataEntryPresent Dz1GifDataEntryPresentFromStrW(wstr_t str)
{
	struct Dz1GifDataEntryPresentMapW *i = NULL;
	for (i = Dz1GifDataEntryPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GifDataEntryPresent_max;
}
#endif // UNIX_SYSTEM

Dz1GifDataEntryPresent *Dz1GifDataEntryPresent_new(Dz1GifDataEntryPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDataEntryPresent *__internal_ret = (Dz1GifDataEntryPresent *)Dz1Calloc(sizeof(Dz1GifDataEntryPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1GifDataEntryPresent_dump(Dz1GifDataEntryPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1GifDataEntryPresentStr(*v));
}
// Dz1GifDataEntryPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataEntry
Dz1GifDataEntry *Dz1GifDataEntry_new(Dz1GifDataEntryPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDataEntry *ret = (Dz1GifDataEntry *)Dz1Calloc(sizeof(Dz1GifDataEntry), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDataEntry_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1GifDataEntryPresent_graphic:
			// _U_cst_clone
			if (ptr != NULL) ret->x.graphic = (Dz1GifGraphic *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifDataEntryPresent_app_ext:
			// _U_cst_clone
			if (ptr != NULL) ret->x.app_ext = (Dz1GifAppExt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifDataEntryPresent_comment:
			// _U_cst_clone
			if (ptr != NULL) ret->x.comment = (Dz1GifCommentExt *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifDataEntryPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDataEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1GifDataEntry_copy(Dz1GifDataEntry *ret, Dz1GifDataEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1GifDataEntryPresent_graphic:
			// _U_cst_clone
			if (src->x.graphic && (ret->x.graphic = Dz1GifGraphic_clone(src->x.graphic, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1GifDataEntryPresent_app_ext:
			// _U_cst_clone
			if (src->x.app_ext && (ret->x.app_ext = Dz1GifAppExt_clone(src->x.app_ext, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		case Dz1GifDataEntryPresent_comment:
			// _U_cst_clone
			if (src->x.comment && (ret->x.comment = Dz1GifCommentExt_clone(src->x.comment, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1GifDataEntry *Dz1GifDataEntry_clone(Dz1GifDataEntry *src, Dz1Error *err)
{
	Dz1GifDataEntry *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1GifDataEntry *)Dz1Calloc(sizeof(Dz1GifDataEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1GifDataEntry_delAndSetNull, (void *)&ret);
		if (Dz1GifDataEntry_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDataEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1GifDataEntry_purge(Dz1GifDataEntry *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1GifDataEntryPresent_graphic:
		Dz1GifGraphic_del(p->x.graphic);
		break;
	case Dz1GifDataEntryPresent_app_ext:
		Dz1GifAppExt_del(p->x.app_ext);
		break;
	case Dz1GifDataEntryPresent_comment:
		Dz1GifCommentExt_del(p->x.comment);
		break;
	default:
		break;
	}
}

void Dz1GifDataEntry_del(Dz1GifDataEntry *p)
{
	if (!p) return;
	Dz1GifDataEntry_purge(p);
	Dz1Free(p);
}

void Dz1GifDataEntry_dump(Dz1GifDataEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1GifDataEntryPresent_graphic:
		Dz1Thread_printf(Dz1T("graphic = ")); Dz1GifGraphic_dump(p->x.graphic, tab); 
		break;
	case Dz1GifDataEntryPresent_app_ext:
		Dz1Thread_printf(Dz1T("app_ext = ")); Dz1GifAppExt_dump(p->x.app_ext, tab); 
		break;
	case Dz1GifDataEntryPresent_comment:
		Dz1Thread_printf(Dz1T("comment = ")); Dz1GifCommentExt_dump(p->x.comment, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1GifDataEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDataArr
static Dz1Error Dz1GifDataArr_add(Dz1GifDataArr *p, Dz1GifDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	err = Dz1Fifo_push(p->storage, data);
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

typedef struct Dz1GifDataArrMkArrArg
{
	Dz1GifDataEntry **arr;
	unsigned int idx;
} Dz1GifDataArrMkArrArg;

static Dz1Error _Dz1GifDataArr_get_array(void *ptr, Dz1GifDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1GifDataArrMkArrArg *arg = (Dz1GifDataArrMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static Dz1GifDataEntry **Dz1GifDataArr_get_array(Dz1GifDataArr *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	Dz1GifDataEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1GifDataEntry **)Dz1Calloc(sizeof(Dz1GifDataEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1GifDataArrMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _Dz1GifDataArr_get_array, (void *)&arg);
		if (ERR_PROBE(errp)) ERR_OUT(errp);
		else
		{
			if (ret_cnt) (*ret_cnt) = cnt;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Memory_cancel, (void *)ret);
	}
	if (ERR_PROBE(errp)) ret = NULL;
	return ret;
}

static Dz1Error Dz1GifDataArr_travelForward(Dz1GifDataArr *p, Dz1Error (*func)(void *ptr, Dz1GifDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelForward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static Dz1Error Dz1GifDataArr_travelBackward(Dz1GifDataArr *p, Dz1Error (*func)(void *ptr, Dz1GifDataEntry *data), void *ptr)
{
	return Dz1Fifo_travelBackward(p->storage, (Dz1FifoTravelFunc)func, ptr);
}

static unsigned int Dz1GifDataArr_count(Dz1GifDataArr *p)
{
	unsigned int ret = Dz1Fifo_count(p->storage);
	return ret;
}

Dz1GifDataArr *Dz1GifDataArr_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDataArr *ret = (Dz1GifDataArr *)Dz1Calloc(sizeof(Dz1GifDataArr), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1GifDataArr_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1Fifo_newDynamic(
				(Dz1DelFunc)Dz1GifDataEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = Dz1GifDataArr_count;
			ret->travel = Dz1GifDataArr_travelForward;
			ret->travelForward = Dz1GifDataArr_travelForward;
			ret->travelBackward = Dz1GifDataArr_travelBackward;
			ret->get_array = Dz1GifDataArr_get_array;
			ret->add = Dz1GifDataArr_add;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDataArr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _Dz1GifDataArr_clone(void *ptr, Dz1GifDataEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1GifDataArr *p = (Dz1GifDataArr *)ptr;
	Dz1GifDataEntry *cloned = Dz1GifDataEntry_clone(data, &err); // normal
	err = Dz1Fifo_push(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

Dz1GifDataArr *Dz1GifDataArr_clone(Dz1GifDataArr *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDataArr *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1GifDataArr_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1GifDataArr_delAndSetNull, (void *)&ret);

		*errp = Dz1Fifo_travelForward(src->storage, (Dz1FifoTravelFunc)_Dz1GifDataArr_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDataArr_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1GifDataArr_purge(Dz1GifDataArr *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_empty(p->storage);
}

void Dz1GifDataArr_del(Dz1GifDataArr *p)
{
	if (!p) return;
	if (p->storage) Dz1Fifo_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _Dz1GifDataArr_dump(void *ptr, Dz1GifDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); Dz1GifDataEntry_dump(p, tab);
	return err;
}

void Dz1GifDataArr_dump(Dz1GifDataArr *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _Dz1GifDataArr_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1GifDataArr
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Gif
Dz1Gif *Dz1Gif_new(Dz1GifHeader *hdr, Dz1GifDescr *descr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Gif *__internal_ret = (Dz1Gif *)Dz1Calloc(sizeof(Dz1Gif), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Gif_delAndSetNull, (void *)&__internal_ret);
		
		if ((__internal_ret->datas = Dz1GifDataArr_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->hdr = hdr;
			__internal_ret->descr = descr;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Gif_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1Gif_copy(Dz1Gif *dst, Dz1Gif *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->hdr && (dst->hdr = Dz1GifHeader_clone(src->hdr, errp)) == NULL) ERR_OUT(errp);
	else if (src->descr && (dst->descr = Dz1GifDescr_clone(src->descr, errp)) == NULL) ERR_OUT(errp);
	else if (src->datas && (dst->datas = Dz1GifDataArr_clone(src->datas, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Gif *Dz1Gif_clone(Dz1Gif *src, Dz1Error *err)
{
	Dz1Gif *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1Gif *)Dz1Calloc(sizeof(Dz1Gif), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Gif_delAndSetNull, (void *)&dst);
		if (Dz1Gif_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Gif_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1Gif_purge(Dz1Gif *p)
{
	if (p == NULL) return;
	Dz1GifHeader_del(p->hdr);
	Dz1GifDescr_del(p->descr);
	Dz1GifDataArr_del(p->datas);
}

void Dz1Gif_del(Dz1Gif *p)
{
	if (p == NULL) return;
	Dz1Gif_purge(p);
	Dz1Free(p);
}

void Dz1Gif_dump(Dz1Gif *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("hdr = ")); Dz1GifHeader_dump(p->hdr, tab); 
		// Normal member
		Dz1Thread_tprintf(tab, Dz1T("descr = ")); Dz1GifDescr_dump(p->descr, tab); 
		Dz1Thread_tprintf(tab, Dz1T("datas = ")); Dz1GifDataArr_dump(p->datas, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1Gif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptParallel
Dz1GifDecodeOptParallel *Dz1GifDecodeOptParallel_new(Dz1Sync *sync, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDecodeOptParallel *__internal_ret = (Dz1GifDecodeOptParallel *)Dz1Calloc(sizeof(Dz1GifDecodeOptParallel), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDecodeOptParallel_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->sync = sync;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDecodeOptParallel_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1GifDecodeOptParallel_purge(Dz1GifDecodeOptParallel *p)
{
	if (p == NULL) return;
	Dz1Sync_del(p->sync);
}

void Dz1GifDecodeOptParallel_del(Dz1GifDecodeOptParallel *p)
{
	if (p == NULL) return;
	Dz1GifDecodeOptParallel_purge(p);
	Dz1Free(p);
}

// Dz1GifDecodeOptParallel
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptSequential
Dz1GifDecodeOptSequential *Dz1GifDecodeOptSequential_new(Dz1GifDecodeOptUserFunc user_handle, 
														 void *user_ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDecodeOptSequential *__internal_ret = (Dz1GifDecodeOptSequential *)Dz1Calloc(sizeof(Dz1GifDecodeOptSequential), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDecodeOptSequential_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->user_handle = user_handle;
		__internal_ret->user_ptr = user_ptr;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDecodeOptSequential_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void Dz1GifDecodeOptSequential_purge(Dz1GifDecodeOptSequential *p)
{
	if (p == NULL) return;
	Dz1BMP_del(p->canvas);
	Dz1BMP_del(p->last);
}

void Dz1GifDecodeOptSequential_del(Dz1GifDecodeOptSequential *p)
{
	if (p == NULL) return;
	Dz1GifDecodeOptSequential_purge(p);
	Dz1Free(p);
}

// Dz1GifDecodeOptSequential
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOptPresent
static struct Dz1GifDecodeOptPresentMapA
{
	str_t str;
	Dz1GifDecodeOptPresent v;
} Dz1GifDecodeOptPresentMapA[] =
{
	{ (char *)"parallel", Dz1GifDecodeOptPresent_parallel },
	{ (char *)"sequential", Dz1GifDecodeOptPresent_sequential },
	{ NULL, Dz1GifDecodeOptPresent_max }
};

str_t Dz1GifDecodeOptPresentStrA(Dz1GifDecodeOptPresent v)
{
	struct Dz1GifDecodeOptPresentMapA *i = NULL;
	for (i = Dz1GifDecodeOptPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifDecodeOptPresent Dz1GifDecodeOptPresentFromStrA(str_t str)
{
	struct Dz1GifDecodeOptPresentMapA *i = NULL;
	for (i = Dz1GifDecodeOptPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GifDecodeOptPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GifDecodeOptPresentMapW
{
	wstr_t str;
	Dz1GifDecodeOptPresent v;
} Dz1GifDecodeOptPresentMapW[] =
{
	{ (wchar_t *)L"parallel", Dz1GifDecodeOptPresent_parallel },
	{ (wchar_t *)L"sequential", Dz1GifDecodeOptPresent_sequential },
	{ NULL, Dz1GifDecodeOptPresent_max }
};

wstr_t Dz1GifDecodeOptPresentStrW(Dz1GifDecodeOptPresent v)
{
	struct Dz1GifDecodeOptPresentMapW *i = NULL;
	for (i = Dz1GifDecodeOptPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GifDecodeOptPresent Dz1GifDecodeOptPresentFromStrW(wstr_t str)
{
	struct Dz1GifDecodeOptPresentMapW *i = NULL;
	for (i = Dz1GifDecodeOptPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GifDecodeOptPresent_max;
}
#endif // UNIX_SYSTEM

Dz1GifDecodeOptPresent *Dz1GifDecodeOptPresent_new(Dz1GifDecodeOptPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDecodeOptPresent *__internal_ret = (Dz1GifDecodeOptPresent *)Dz1Calloc(sizeof(Dz1GifDecodeOptPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1GifDecodeOptPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GifDecodeOpt
Dz1GifDecodeOpt *Dz1GifDecodeOpt_new(Dz1GifDecodeOptPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GifDecodeOpt *ret = (Dz1GifDecodeOpt *)Dz1Calloc(sizeof(Dz1GifDecodeOpt), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1GifDecodeOpt_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1GifDecodeOptPresent_parallel:
			// _U_cst_clone
			if (ptr != NULL) ret->x.parallel = (Dz1GifDecodeOptParallel *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifDecodeOptPresent_sequential:
			// _U_cst_clone
			if (ptr != NULL) ret->x.sequential = (Dz1GifDecodeOptSequential *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1GifDecodeOptPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1GifDecodeOpt_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1GifDecodeOpt_purge(Dz1GifDecodeOpt *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1GifDecodeOptPresent_parallel:
		Dz1GifDecodeOptParallel_del(p->x.parallel);
		break;
	case Dz1GifDecodeOptPresent_sequential:
		Dz1GifDecodeOptSequential_del(p->x.sequential);
		break;
	default:
		break;
	}
}

void Dz1GifDecodeOpt_del(Dz1GifDecodeOpt *p)
{
	if (!p) return;
	Dz1GifDecodeOpt_purge(p);
	Dz1Free(p);
}

// Dz1GifDecodeOpt
////////////////////////////////////////////////////////////////////////////////


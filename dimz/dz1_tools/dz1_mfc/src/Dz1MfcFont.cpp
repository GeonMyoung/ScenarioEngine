#include "stdafx.h"
#include "Dz1MfcFontDef.h"

Dz1MfcFontEntry *Dz1MfcFontEntry_new(Dz1Str name, Dz1Str font_name, u16_t font_size, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1MfcFontEntry *__internal_ret = (Dz1MfcFontEntry *)Dz1Calloc(sizeof(Dz1MfcFontEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		CFont *f = NULL;
		pthread_cleanup_push(Dz1MfcFontEntry_delAndSetNull, (void *)&__internal_ret);

		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (font_name && (__internal_ret->font_name = Dz1Str_clone(font_name, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->font = f = new CFont()) == NULL) ERR_SET_OUT(errp, ENOMEM);
		else if (f->CreatePointFont(font_size, font_name) == FALSE) ERR_SET_OUT(errp, EFAULT);
		else
		{
			__internal_ret->font_size = font_size;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1MfcFontEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

Dz1MfcFontEntry *Dz1MfcFontEntry_clone(Dz1MfcFontEntry *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MfcFontEntry *ret = NULL;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((ret = Dz1MfcFontEntry_new(src->name, src->font_name, src->font_size, errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return ret;
}

void Dz1MfcFontEntry_del(Dz1MfcFontEntry *p)
{
	if (p == NULL) return;
	if (p->name) Dz1Str_del(p->name);
	if (p->font_name) Dz1Str_del(p->font_name);
	if (p->font != NULL)
	{
		CFont *f = (CFont *)p->font;
		delete f;
		p->font = NULL;
	}
	Dz1Free(p);
}



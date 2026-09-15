////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_riff.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffDataPresent
static struct Dz1RiffDataPresentMapA
{
	str_t str;
	Dz1RiffDataPresent v;
} Dz1RiffDataPresentMapA[] =
{
	{ (char *)"wave", Dz1RiffDataPresent_wave },
	{ NULL, Dz1RiffDataPresent_max }
};

str_t Dz1RiffDataPresentStrA(Dz1RiffDataPresent v)
{
	struct Dz1RiffDataPresentMapA *i = NULL;
	for (i = Dz1RiffDataPresentMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1RiffDataPresent Dz1RiffDataPresentFromStrA(str_t str)
{
	struct Dz1RiffDataPresentMapA *i = NULL;
	for (i = Dz1RiffDataPresentMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1RiffDataPresent_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1RiffDataPresentMapW
{
	wstr_t str;
	Dz1RiffDataPresent v;
} Dz1RiffDataPresentMapW[] =
{
	{ (wchar_t *)L"wave", Dz1RiffDataPresent_wave },
	{ NULL, Dz1RiffDataPresent_max }
};

wstr_t Dz1RiffDataPresentStrW(Dz1RiffDataPresent v)
{
	struct Dz1RiffDataPresentMapW *i = NULL;
	for (i = Dz1RiffDataPresentMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1RiffDataPresent Dz1RiffDataPresentFromStrW(wstr_t str)
{
	struct Dz1RiffDataPresentMapW *i = NULL;
	for (i = Dz1RiffDataPresentMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1RiffDataPresent_max;
}
#endif // UNIX_SYSTEM

Dz1RiffDataPresent *Dz1RiffDataPresent_new(Dz1RiffDataPresent *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffDataPresent *__internal_ret = (Dz1RiffDataPresent *)Dz1Calloc(sizeof(Dz1RiffDataPresent), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}

void Dz1RiffDataPresent_dump(Dz1RiffDataPresent *v, int tab)
{
	if (v == NULL) Dz1Thread_printf(Dz1T("NULL\n"));
	else Dz1Thread_printf(Dz1T("%s\n"), Dz1RiffDataPresentStr(*v));
}
// Dz1RiffDataPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1RiffData
Dz1RiffData *Dz1RiffData_new(Dz1RiffDataPresent present, void *ptr, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1RiffData *ret = (Dz1RiffData *)Dz1Calloc(sizeof(Dz1RiffData), 1, errp);
	if (ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1RiffData_delAndSetNull, (void *)&ret);

		ret->present = present;
		switch(ret->present)
		{
		case Dz1RiffDataPresent_wave:
			// _U_cst_clone
			if (ptr != NULL) ret->x.wave = (Dz1RiffWave *)ptr;
			ERR_CLEAR(errp);
			break;
		case Dz1RiffDataPresent_max:
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1RiffData_copy(Dz1RiffData *ret, Dz1RiffData *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL || ret == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else
	{
		ret->present = src->present;
		switch(src->present)
		{
		case Dz1RiffDataPresent_wave:
			// _U_cst_clone
			if (src->x.wave && (ret->x.wave = Dz1RiffWave_clone(src->x.wave, errp)) == NULL) ERR_OUT(errp);
			else {ERR_CLEAR(errp); }
			break;
		default:
			ERR_SET_OUT(errp, EINVAL);
			break;
		}
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1RiffData *Dz1RiffData_clone(Dz1RiffData *src, Dz1Error *err)
{
	Dz1RiffData *ret = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { errp->code = EINVAL; ERR_OUT(errp); }
	else if ((ret = (Dz1RiffData *)Dz1Calloc(sizeof(Dz1RiffData), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1RiffData_delAndSetNull, (void *)&ret);
		if (Dz1RiffData_copy(ret, src, errp) == FALSE) { ERR_OUT(errp); }
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1RiffData_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1RiffData_purge(Dz1RiffData *p)
{
	if (!p) return;
	switch(p->present)
	{
	case Dz1RiffDataPresent_wave:
		Dz1RiffWave_del(p->x.wave);
		break;
	default:
		break;
	}
}

void Dz1RiffData_del(Dz1RiffData *p)
{
	if (!p) return;
	Dz1RiffData_purge(p);
	Dz1Free(p);
}

void Dz1RiffData_dump(Dz1RiffData *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else switch(p->present)
	{
	case Dz1RiffDataPresent_wave:
		Dz1Thread_printf(Dz1T("wave = ")); Dz1RiffWave_dump(p->x.wave, tab); 
		break;
	default:
		Dz1Thread_tprintf(tab, Dz1T("??? = %d\n"), p->present);
		break;
	}
}

// Dz1RiffData
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1Riff
Dz1Riff *Dz1Riff_new(Dz1RiffData *data, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1Riff *__internal_ret = (Dz1Riff *)Dz1Calloc(sizeof(Dz1Riff), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(Dz1Riff_delAndSetNull, (void *)&__internal_ret);
		
		__internal_ret->data = data;
		ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Riff_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t Dz1Riff_copy(Dz1Riff *dst, Dz1Riff *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->data && (dst->data = Dz1RiffData_clone(src->data, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

Dz1Riff *Dz1Riff_clone(Dz1Riff *src, Dz1Error *err)
{
	Dz1Riff *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (Dz1Riff *)Dz1Calloc(sizeof(Dz1Riff), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1Riff_delAndSetNull, (void *)&dst);
		if (Dz1Riff_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (Dz1Riff_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void Dz1Riff_purge(Dz1Riff *p)
{
	if (p == NULL) return;
	Dz1RiffData_del(p->data);
}

void Dz1Riff_del(Dz1Riff *p)
{
	if (p == NULL) return;
	Dz1Riff_purge(p);
	Dz1Free(p);
}

void Dz1Riff_dump(Dz1Riff *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("data.")); Dz1RiffData_dump(p->data, tab); 
	}
}
// Dz1Riff
////////////////////////////////////////////////////////////////////////////////


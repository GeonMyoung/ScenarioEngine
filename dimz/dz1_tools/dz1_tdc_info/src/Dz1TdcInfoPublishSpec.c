#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_fifo.h>
#include <dz1_aatree.h>
#include <dz1_thread_stdio.h>

#include "Dz1TdcInfoPublishSpec.h"

typedef struct NativeStorageStrMap
{
	NativeStorage			v;
	str_t					s;
} NativeStorageStrMap;
static NativeStorageStrMap nativeStorageStrMap[] =
{
	{ NativeStorage_data, "data" },
	{ NativeStorage_address, "pointer" },
	{ NativeStorage_none, "sizeless" },
	{ -1, "unknown" },
};

str_t NativeStorageStr(NativeStorage src)
{
	NativeStorageStrMap *i = NULL;
	for (i = nativeStorageStrMap; i->v != -1; i++)
		if (i->v == src) break;
	return i->s;
}

///////////////////////////////////////////////////////////////////////////////
// Basic Spec
///////////////////////////////////////////////////////////////////////////////
PublishBasicSpec *PublishBasicSpec_new(str_t cpplink, str_t dllport, 
									   str_t printf, str_t printfA, str_t printfW, 
									   str_t tprintf, str_t tprintfA, str_t tprintfW,
									   str_t fprintf, str_t fprintfA, str_t fprintfW, 
									   str_t ftprintf, str_t ftprintfA, str_t ftprintfW, 
									   Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishBasicSpec *ret = (PublishBasicSpec *)Dz1Calloc(sizeof(PublishBasicSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishBasicSpec_delAndSetNull, (void *)&ret);

		if (cpplink && (ret->cpplink = Dz1Str_dup(cpplink, errp)) == NULL) ERR_OUT(errp);
		else if (dllport && (ret->dllport = Dz1Str_dup(dllport, errp)) == NULL) ERR_OUT(errp);

		else if (printf && (ret->printf[0] = Dz1Str_dup(printf, errp)) == NULL) ERR_OUT(errp);
		else if (printfA && (ret->printf[1] = Dz1Str_dup(printfA, errp)) == NULL) ERR_OUT(errp);
		else if (printfW && (ret->printf[2] = Dz1Str_dup(printfW, errp)) == NULL) ERR_OUT(errp);

		else if (tprintf && (ret->tprintf[0] = Dz1Str_dup(tprintf, errp)) == NULL) ERR_OUT(errp);
		else if (tprintfA && (ret->tprintf[1] = Dz1Str_dup(tprintfA, errp)) == NULL) ERR_OUT(errp);
		else if (tprintfW && (ret->tprintf[2] = Dz1Str_dup(tprintfW, errp)) == NULL) ERR_OUT(errp);

		else if (fprintf && (ret->fprintf[0] = Dz1Str_dup(fprintf, errp)) == NULL) ERR_OUT(errp);
		else if (fprintfA && (ret->fprintf[1] = Dz1Str_dup(fprintfA, errp)) == NULL) ERR_OUT(errp);
		else if (fprintfW && (ret->fprintf[2] = Dz1Str_dup(fprintfW, errp)) == NULL) ERR_OUT(errp);

		else if (ftprintf && (ret->ftprintf[0] = Dz1Str_dup(ftprintf, errp)) == NULL) ERR_OUT(errp);
		else if (ftprintfA && (ret->ftprintf[1] = Dz1Str_dup(ftprintfA, errp)) == NULL) ERR_OUT(errp);
		else if (ftprintfW && (ret->ftprintf[2] = Dz1Str_dup(ftprintfW, errp)) == NULL) ERR_OUT(errp);

		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (PublishBasicSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishBasicSpec_del(PublishBasicSpec *p)
{
	if (!p) return;
	if (p->cpplink) Dz1Str_del(p->cpplink);
	if (p->dllport) Dz1Str_del(p->dllport);

	if (p->printf[0]) Dz1Str_del(p->printf[0]);
	if (p->printf[1]) Dz1Str_del(p->printf[1]);
	if (p->printf[2]) Dz1Str_del(p->printf[2]);

	if (p->tprintf[0]) Dz1Str_del(p->tprintf[0]);
	if (p->tprintf[1]) Dz1Str_del(p->tprintf[1]);
	if (p->tprintf[2]) Dz1Str_del(p->tprintf[2]);

	if (p->fprintf[0]) Dz1Str_del(p->fprintf[0]);
	if (p->fprintf[1]) Dz1Str_del(p->fprintf[1]);
	if (p->fprintf[2]) Dz1Str_del(p->fprintf[2]);

	if (p->ftprintf[0]) Dz1Str_del(p->ftprintf[0]);
	if (p->ftprintf[1]) Dz1Str_del(p->ftprintf[1]);
	if (p->ftprintf[2]) Dz1Str_del(p->ftprintf[2]);

	Dz1Free(p);
}

void PublishBasicSpec_dump(PublishBasicSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "c++ link prefix = %s\n", p->cpplink);
	Dz1Thread_tprintf(tab, "win32 dll import/export prefix = %s\n", p->dllport);
	Dz1Thread_tprintf(tab, "printf api = %s, %s, %s\n", p->printf[0], p->printf[1], p->printf[2]);
	Dz1Thread_tprintf(tab, "tab printf api = %s, %s, %s\n", p->tprintf[0], p->tprintf[1], p->tprintf[2]);
	Dz1Thread_tprintf(tab, "file tab printf api = %s, %s, %s\n", p->ftprintf[0], p->ftprintf[1], p->ftprintf[2]);
}

///////////////////////////////////////////////////////////////////////////////
// Cast Spec
///////////////////////////////////////////////////////////////////////////////
PublishCastSpec *PublishCastSpec_new(str_t del, str_t cmp, str_t dump, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishCastSpec *ret = (PublishCastSpec *)Dz1Calloc(sizeof(PublishCastSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishCastSpec_delAndSetNull, (void *)&ret);

		if (del && (ret->del = Dz1Str_dup(del, errp)) == NULL) ERR_OUT(errp);
		else if (cmp && (ret->cmp = Dz1Str_dup(cmp, errp)) == NULL) ERR_OUT(errp);
		else if (dump && (ret->dump = Dz1Str_dup(dump, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (PublishCastSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishCastSpec_del(PublishCastSpec *p)
{
	if (!p) return;
	if (p->del) Dz1Str_del(p->del);
	if (p->cmp) Dz1Str_del(p->cmp);
	if (p->dump) Dz1Str_del(p->dump);
	Dz1Free(p);
}

void PublishCastSpec_dump(PublishCastSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "del fuinction type = %s\n", p->del);
	Dz1Thread_tprintf(tab, "compare fuinction type = %s\n", p->cmp);
	Dz1Thread_tprintf(tab, "dump fuinction type = %s\n", p->dump);
}

///////////////////////////////////////////////////////////////////////////////
// Memory Func Spec
///////////////////////////////////////////////////////////////////////////////
PublishMemFuncSpec *PublishMemFuncSpec_new(bool_t allocNeedErrorPtr, str_t malloc, str_t calloc, str_t free, str_t cancel, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishMemFuncSpec *ret = (PublishMemFuncSpec *)Dz1Calloc(sizeof(PublishMemFuncSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->allocNeedErrorPtr = allocNeedErrorPtr;
		pthread_cleanup_push(PublishMemFuncSpec_delAndSetNull, (void *)&ret);

		if (malloc && (ret->malloc= Dz1Str_dup(malloc, errp)) == NULL) ERR_OUT(errp);
		else if (calloc && (ret->calloc = Dz1Str_dup(calloc, errp)) == NULL) ERR_OUT(errp);
		else if (free && (ret->free = Dz1Str_dup(free, errp)) == NULL) ERR_OUT(errp);
		else if (cancel && (ret->cancel = Dz1Str_dup(cancel, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (PublishMemFuncSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishMemFuncSpec_del(PublishMemFuncSpec *p)
{
	if (!p) return;
	if (p->malloc) Dz1Str_del(p->malloc);
	if (p->calloc) Dz1Str_del(p->calloc);
	if (p->free) Dz1Str_del(p->free);
	if (p->cancel) Dz1Str_del(p->cancel);
	Dz1Free(p);
}

void PublishMemFuncSpec_dump(PublishMemFuncSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "malloc api = void *%s(size_t%s)\n", p->malloc, p->allocNeedErrorPtr ? ", ErrorType *" : "");
	Dz1Thread_tprintf(tab, "calloc api = void *%s(size_t, int%s)\n", p->calloc, p->allocNeedErrorPtr ? ", ErrorType *" : "");
	Dz1Thread_tprintf(tab, "free api = void %s(void *)\n", p->free);
	Dz1Thread_tprintf(tab, "cancel api = void %s(void *)\n", p->cancel);
}

///////////////////////////////////////////////////////////////////////////////
// Post Fix Spec
///////////////////////////////////////////////////////////////////////////////
void PublishPostFix_lengthFix(PublishPostFix *ret)
{
	int len;
	if (ret->_new && ret->lenMax < (len = (int)strlen(ret->_new))) ret->lenMax = len;
	if (ret->_del && ret->lenMax < (len = (int)strlen(ret->_del))) ret->lenMax = len;
	if (ret->_delAndSetNull && ret->lenMax < (len = (int)strlen(ret->_delAndSetNull))) ret->lenMax = len;
	if (ret->_dump && ret->lenMax < (len = (int)strlen(ret->_dump))) ret->lenMax = len;
	if (ret->_cmp && ret->lenMax < (len = (int)strlen(ret->_cmp))) ret->lenMax = len;
	if (ret->_clone && ret->lenMax < (len = (int)strlen(ret->_clone))) ret->lenMax = len;
	if (ret->_enc && ret->lenMax < (len = (int)strlen(ret->_enc))) ret->lenMax = len;
	if (ret->_dec && ret->lenMax < (len = (int)strlen(ret->_dec))) ret->lenMax = len;
}
 
PublishPostFix *PublishPostFix_new(str_t _new, str_t _gen, str_t _purge, str_t _del, str_t _delAndSetNull, str_t _dump, str_t _fdump,
								   str_t _cmp, str_t _clone, str_t _copy, str_t _enc, str_t _dec, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishPostFix *ret = (PublishPostFix *)Dz1Calloc(sizeof(PublishPostFix), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishPostFix_delAndSetNull, (void *)&ret);

		if (_new && (ret->_new = Dz1Str_dup(_new, errp)) == NULL) ERR_OUT(errp);
		else if (_gen && (ret->_gen = Dz1Str_dup(_gen, errp)) == NULL) ERR_OUT(errp);
		else if (_purge && (ret->_purge = Dz1Str_dup(_purge, errp)) == NULL) ERR_OUT(errp);
		else if (_del && (ret->_del = Dz1Str_dup(_del, errp)) == NULL) ERR_OUT(errp);
		else if (_delAndSetNull && (ret->_delAndSetNull = Dz1Str_dup(_delAndSetNull, errp)) == NULL) ERR_OUT(errp);
		else if (_dump && (ret->_dump = Dz1Str_dup(_dump, errp)) == NULL) ERR_OUT(errp);
		else if (_fdump && (ret->_fdump = Dz1Str_dup(_fdump, errp)) == NULL) ERR_OUT(errp);
		else if (_cmp && (ret->_cmp = Dz1Str_dup(_cmp, errp)) == NULL) ERR_OUT(errp);
		else if (_clone && (ret->_clone = Dz1Str_dup(_clone, errp)) == NULL) ERR_OUT(errp);
		else if (_copy && (ret->_copy = Dz1Str_dup(_copy, errp)) == NULL) ERR_OUT(errp);
		else if (_enc && (ret->_enc = Dz1Str_dup(_enc, errp)) == NULL) ERR_OUT(errp);
		else if (_dec && (ret->_dec = Dz1Str_dup(_dec, errp)) == NULL) ERR_OUT(errp);
		else
		{
			PublishPostFix_lengthFix(ret);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (PublishPostFix_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishPostFix_del(PublishPostFix *p)
{
	if (!p) return;
	if (p->_new) Dz1Str_del(p->_new);
	if (p->_gen) Dz1Str_del(p->_gen);
	if (p->_purge) Dz1Str_del(p->_purge);
	if (p->_del) Dz1Str_del(p->_del);
	if (p->_delAndSetNull) Dz1Str_del(p->_delAndSetNull);
	if (p->_dump) Dz1Str_del(p->_dump);
	if (p->_fdump) Dz1Str_del(p->_fdump);
	if (p->_cmp) Dz1Str_del(p->_cmp);
	if (p->_clone) Dz1Str_del(p->_clone);
	if (p->_copy) Dz1Str_del(p->_copy);
	if (p->_enc) Dz1Str_del(p->_enc);
	if (p->_dec) Dz1Str_del(p->_dec);
	Dz1Free(p);
}

void PublishPostFix_dump(PublishPostFix *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "new api postfix = (%s)\n", p->_new);
	Dz1Thread_tprintf(tab, "gen api postfix = (%s)\n", p->_gen);
	Dz1Thread_tprintf(tab, "delete api postfix = (%s)\n", p->_del);
	Dz1Thread_tprintf(tab, "del and set NULL api postfix = (%s)\n", p->_delAndSetNull);
	Dz1Thread_tprintf(tab, "dump api postfix = (%s)\n", p->_dump);
	Dz1Thread_tprintf(tab, "compare api postfix = (%s)\n", p->_cmp);
	Dz1Thread_tprintf(tab, "clone api postfix = (%s)\n", p->_clone);
	Dz1Thread_tprintf(tab, "encode api postfix = (%s)\n", p->_enc);
	Dz1Thread_tprintf(tab, "decode api postfix = (%s)\n", p->_dec);
}

///////////////////////////////////////////////////////////////////////////////
// Error Spec Entry
///////////////////////////////////////////////////////////////////////////////
PublishErrorSpecEntry *PublishErrorSpecEntry_new(str_t name, bool_t argIsPtr, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishErrorSpecEntry *ret = (PublishErrorSpecEntry *)Dz1Calloc(sizeof(PublishErrorSpecEntry), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ret->argIsPtr = argIsPtr;
		pthread_cleanup_push(PublishErrorSpecEntry_delAndSetNull, (void *)&ret);

		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (PublishErrorSpecEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishErrorSpecEntry_del(PublishErrorSpecEntry *p)
{
	if (!p) return;
	if (p->name) Dz1Str_del(p->name);
	Dz1Free(p);
}

void PublishErrorSpecEntry_dump(PublishErrorSpecEntry *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s(%s)", p->name, p->argIsPtr ? "*" : "");
}

///////////////////////////////////////////////////////////////////////////////
// Error Spec
///////////////////////////////////////////////////////////////////////////////
static str_t PublishErrorSpec_code(struct PublishErrorSpec *p, char buf[1024], ErrorCodeGenType type, str_t var, str_t arg)
{
	bool_t isPointer = FALSE;
	if (var[0] == '*') { isPointer = TRUE; var++; }

	switch(type)
	{
		case ErrorCodeGenType_init:
			if (isPointer)
				sprintf(buf, "%s ? %s : &%s", var, var, arg);
			else
				sprintf(buf, "%s", p->defaultVal);
			break;
		case ErrorCodeGenType_set:
			if (p->print->argIsPtr)
				sprintf(buf, "%s(%s%s, %s)", p->set->name, isPointer ? "" : "&", var, arg);
			else
				sprintf(buf, "%s(%s%s, %s)", p->set->name, isPointer ? "*" : "", var, arg);
			break;
		case ErrorCodeGenType_print:
			if (p->print->argIsPtr)
				sprintf(buf, "%s(%s%s)", p->print->name, isPointer ? "" : "&", var);
			else
				sprintf(buf, "%s(%s%s)", p->print->name, isPointer ? "*" : "", var);
			break;
		case ErrorCodeGenType_setAndPrint:
			if (p->setAndPrint->argIsPtr)
				sprintf(buf, "%s(%s%s, %s)", p->setAndPrint->name, isPointer ? "" : "&", var, arg);
			else
				sprintf(buf, "%s(%s%s, %s)", p->setAndPrint->name, isPointer ? "*" : "", var, arg);
			break;
		case ErrorCodeGenType_probe:
			if (p->probe->argIsPtr)
				sprintf(buf, "%s(%s%s)", p->probe->name, isPointer ? "" : "&", var);
			else
				sprintf(buf, "%s(%s%s)", p->probe->name, isPointer ? "*" : "", var);
			break;
		case ErrorCodeGenType_clear:
			if (p->clear->argIsPtr)
				sprintf(buf, "%s(%s%s)", p->clear->name, isPointer ? "" : "&", var);
			else
				sprintf(buf, "%s(%s%s)", p->clear->name, isPointer ? "*" : "", var);
			break;
		default:
			Dz1Thread_printf("Unknown Code Gen Type : %d\n", type);
			abort();
	}
	return buf;
}

PublishErrorSpec *PublishErrorSpec_new(str_t type, str_t defaultVal,
										PublishErrorSpecEntry	*set,
										PublishErrorSpecEntry	*print,
										PublishErrorSpecEntry	*setAndPrint,
										PublishErrorSpecEntry	*probe,
										PublishErrorSpecEntry	*clear, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishErrorSpec *ret = (PublishErrorSpec *)Dz1Calloc(sizeof(PublishErrorSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishErrorSpec_delAndSetNull, (void *)&ret);

		if (type && (ret->type = Dz1Str_dup(type, errp)) == NULL) ERR_OUT(errp);
		else if (defaultVal && (ret->defaultVal = Dz1Str_dup(defaultVal, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->set = set;
			ret->print = print;
			ret->setAndPrint = setAndPrint;
			ret->probe = probe;
			ret->clear = clear;
			ret->code = PublishErrorSpec_code;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (PublishErrorSpec_delAndSetNull, (void *)&ret);
	}
	return ret;

}

void PublishErrorSpec_del(PublishErrorSpec *p)
{
	if (!p) return;
	if (p->type) Dz1Str_del(p->type);
	if (p->defaultVal) Dz1Str_del(p->defaultVal);
	if (p->set) PublishErrorSpecEntry_del(p->set);
	if (p->print) PublishErrorSpecEntry_del(p->print);
	if (p->setAndPrint) PublishErrorSpecEntry_del(p->setAndPrint);
	if (p->probe) PublishErrorSpecEntry_del(p->probe);
	if (p->clear) PublishErrorSpecEntry_del(p->clear);
	Dz1Free(p);
}

void PublishErrorSpec_dump(PublishErrorSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "error type = %s\n", p->type);
	Dz1Thread_tprintf(tab, "initial value = %s\n", p->defaultVal);
	if (p->print)
	{
		Dz1Thread_tprintf(tab, "print api = ");
		PublishErrorSpecEntry_dump(p->print, 0);
		Dz1Thread_tprintf(0, "\n");
	}
	if (p->setAndPrint)
	{
		Dz1Thread_tprintf(tab, "set and print api = ");
		PublishErrorSpecEntry_dump(p->setAndPrint, 0);
		Dz1Thread_tprintf(0, "\n");
	}
	if (p->probe)
	{
		Dz1Thread_tprintf(tab, "error probe api = ");
		PublishErrorSpecEntry_dump(p->probe, 0);
		Dz1Thread_tprintf(0, "\n");
	}
	if (p->clear)
	{
		Dz1Thread_tprintf(tab, "error clear api = ");
		PublishErrorSpecEntry_dump(p->clear, 0);
		Dz1Thread_tprintf(0, "\n");
	}
}

///////////////////////////////////////////////////////////////////////////////
// Array Spec
///////////////////////////////////////////////////////////////////////////////
static void PublishArraySpecApiMap_del(PublishArraySpecApiMap *p)
{
	if (!p) return;
	if (p->name) Dz1Str_del(p->name);
	Dz1Free(p);
}

static void PublishArraySpecApiMap_delAndSetNull(void *ptr)
{
	PublishArraySpecApiMap **p = (PublishArraySpecApiMap **)ptr;
	PublishArraySpecApiMap_del(*p); *p = NULL;
}

static PublishArraySpecApiMap *PublishArraySpecApiMap_new(ArraySpecCallType type, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishArraySpecApiMap *ret = (PublishArraySpecApiMap *)Dz1Calloc(sizeof(PublishArraySpecApiMap), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishArraySpecApiMap_delAndSetNull, (void *)&ret);
		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->type = type;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (PublishArraySpecApiMap_delAndSetNull, (void *)&ret);
	}
	return ret;
}

//static Dz1Error PublishArraySpec_addMap(PublishArraySpec *p, ArraySpecApiType apiType, ArraySpecCallType callType, str_t name)
static bool_t PublishArraySpec_addMap(PublishArraySpec *p, ArraySpecApiType apiType, ArraySpecCallType callType, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (p->map[apiType]) ERR_SET_OUT(errp, EEXIST);
	else if ((p->map[apiType] = PublishArraySpecApiMap_new(callType, name, errp)) == NULL) ERR_OUT(errp);

//	return err;
	return errp->code == 0 ? TRUE : FALSE;
}

static str_t _getApiName(PublishArraySpec *p, ArraySpecApiType type, str_t storage, bool_t isPointer, char buf[1024])
{
	PublishArraySpecApiMap *m = p->map[type];
	if (m == NULL) return NULL;

	if (m->type == ArraySpecCallType_method)
		sprintf(buf, "%s%s%s", storage, isPointer ? "->" : ".", m->name);
	else
		sprintf(buf, "%s", m->name);

	return buf;
}

static str_t PublishArraySpec_apiName(PublishArraySpec *p, str_t buf, ArraySpecApiType type, str_t object)
{
	bool_t isPointer = FALSE;
	if (*object == '*') { isPointer = TRUE; object++; }
	return _getApiName(p, type, object, isPointer, buf);
}

static int _getPrevName(char prevName[1024], str_t object)
{
	bool_t prevIsPointer = FALSE;
	int len = (int)strlen(object);
	char *cp = prevName + len - 1;
	strcpy(prevName, object);
	while(*cp != '.' && *cp != '>') cp--;
	if (*cp == '>') { prevIsPointer = TRUE; cp--; }
	*cp = '\0';
	return prevIsPointer;
}

static str_t PublishArraySpec_code(PublishArraySpec *p, PublishCastSpec *cast, str_t buf, ArraySpecApiType type,
									str_t storage, str_t arg0, str_t arg1, str_t arg2, str_t arg3)
{
	char name[1024];
	bool_t isPointer = FALSE;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (*storage == '*') { isPointer = TRUE; storage++; }
	switch(type)
	{
		case ArraySpecApiType_new:
			if (p->createNeedCmp)
				sprintf(buf, "%s((%s)%s, (%s)%s, (%s)%s, %s)",
						_getApiName(p, type, storage, isPointer, name),
						cast->cmp, arg0, cast->del, arg1, cast->dump, arg2, arg3);
			else
				sprintf(buf, "%s((%s)%s, (%s)%s, %s)",
						_getApiName(p, type, storage, isPointer, name),
						cast->del, arg0, cast->dump, arg1, arg2);
			break;
		case ArraySpecApiType_purge:
			if (!isPointer)
			{
				Dz1Thread_printf("PublishArraySpec_code() : Delete Code Generator : object should be pointer!\n");
				abort();
			}
			sprintf(buf, "%s(%s)", _getApiName(p, type, storage, isPointer, name), storage);
			break;
		case ArraySpecApiType_del:
			if (!isPointer)
			{
				Dz1Thread_printf("PublishArraySpec_code() : Delete Code Generator : object should be pointer!\n");
				abort();
			}
			sprintf(buf, "%s(%s)", _getApiName(p, type, storage, isPointer, name), storage);
			break;
		case ArraySpecApiType_delAndSetNull:
			if (!isPointer)
			{
				Dz1Thread_printf("PublishArraySpec_code() : DeleteAndSetNull  Code Generator : object should be pointer!\n");
				abort();
			}
			sprintf(buf, "%s((void *)&%s)", _getApiName(p, type, storage, isPointer, name), storage);
			break;
		case ArraySpecApiType_add:
		case ArraySpecApiType_remove:
			sprintf(buf, "%s(%s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage, arg0);
			break;
		case ArraySpecApiType_travelForward:
		case ArraySpecApiType_travelBackward:
			sprintf(buf, "%s(%s%s, %s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage,
					p->travelFuncCast ? p->travelFuncCast : "", arg0, arg1);
			break;
		//////////////////////////////////
		// Optional
		//////////////////////////////////
// 		case ArraySpecApiType_dump:	// arg1 = "A" or "W"
// 			if (p->map[type] != NULL)
// 				sprintf(buf, "%s(%s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage, arg0);
// 			else
// 			{
// 				char prevName[1024];
// 				bool_t prevIsPointer = _getPrevName(prevName, storage);
// 				sprintf(buf, "%s%sdump(%s%s, %s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName, arg0);
// 			}
// 			break;
		case ArraySpecApiType_clone:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage, arg0);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%sclone(%s%s, %s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName, arg0);
			}
			break;
		case ArraySpecApiType_extract:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage, arg0);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%sextract(%s%s, %s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName, arg0);
			}
			break;
		case ArraySpecApiType_find:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s, %s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage, arg0);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%sfind(%s%s, %s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName, arg0);
			}
			break;
		case ArraySpecApiType_gethead:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%sgethead(%s%s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName);
			}
			break;
		case ArraySpecApiType_gettail:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%sgettail(%s%s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName);
			}
			break;
		case ArraySpecApiType_cnt:
			if (p->map[type] != NULL)
				sprintf(buf, "%s(%s%s)", _getApiName(p, type, storage, isPointer, name), isPointer ? "" : "&", storage);
			else
			{
				char prevName[1024];
				bool_t prevIsPointer = _getPrevName(prevName, storage);
				sprintf(buf, "%s%scount(%s%s)", prevName, prevIsPointer ? "->" : ".", prevIsPointer ? "" : "&", prevName);
			}
			break;
#ifndef CPP_BUILDER_WIN32
		default:
			ERR_SET_OUT(&err, EINVAL);
			abort();
			break;
#endif
	}
	return buf;
}

PublishArraySpec *PublishArraySpec_new(str_t name, bool_t createNeedCmp, str_t travelFuncCast, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishArraySpec *ret = (PublishArraySpec *)Dz1Calloc(sizeof(PublishArraySpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishArraySpec_delAndSetNull, (void *)&ret);

		if (name && (ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else if (travelFuncCast && (ret->travelFuncCast = Dz1Str_dup(travelFuncCast, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->createNeedCmp = createNeedCmp;
			ret->addMap = PublishArraySpec_addMap;
			ret->apiName = PublishArraySpec_apiName;
			ret->code = PublishArraySpec_code;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (PublishErrorSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishArraySpec_del(PublishArraySpec *p)
{
	int i;
	if (!p) return;
	if (p->name) Dz1Str_del(p->name);
	if (p->travelFuncCast) Dz1Str_del(p->travelFuncCast);
	for (i = 0; i < ArraySpecApiType_max; i++)
	{
		if (p->map[i]) PublishArraySpecApiMap_del(p->map[i]);
		p->map[i] = NULL;
	}
	Dz1Free(p);
}

static struct ArraySpecApiTypeMap
{
	ArraySpecApiType type;
	str_t name;
} ArraySpecApiTypeMap[] = 
{
	{ ArraySpecApiType_new,				"new" },
	{ ArraySpecApiType_del,				"del" },
	{ ArraySpecApiType_delAndSetNull,	"del and set NULL" },
//	{ ArraySpecApiType_dump, "dump" },
	{ ArraySpecApiType_clone,			"clone" },
	{ ArraySpecApiType_add,				"add" },
	{ ArraySpecApiType_remove,			"remove" },
	{ ArraySpecApiType_travelForward,	"travelForward" },
	{ ArraySpecApiType_travelBackward,	"travelBackward" },
	{ ArraySpecApiType_cnt,				"count" },
	{ ArraySpecApiType_extract,			"extract" },
	{ ArraySpecApiType_find,			"find" },
	{ ArraySpecApiType_gethead,			"get head" },
	{ ArraySpecApiType_gettail,			"get tail" },
	{ ArraySpecApiType_max,				"unknown"}
};

static struct ArraySpecApiTypeMap api_map[] =
{
	{ ArraySpecApiType_new,				"new" },
	{ ArraySpecApiType_purge,			"purge" },
	{ ArraySpecApiType_del,				"del" },
	{ ArraySpecApiType_delAndSetNull,	"delAndSetNull" },
//	{ ArraySpecApiType_dump,			"dump" },
	{ ArraySpecApiType_clone,			"clone" },
	{ ArraySpecApiType_add,				"add" },
	{ ArraySpecApiType_remove,			"remove" },
	{ ArraySpecApiType_travelForward,	"travelForward" },
	{ ArraySpecApiType_travelBackward,	"travelBackward" },
	{ ArraySpecApiType_cnt,				"count" },
	{ ArraySpecApiType_extract,			"extract" },
	{ ArraySpecApiType_find,			"find" },
	{ ArraySpecApiType_gethead,			"gethead" },
	{ ArraySpecApiType_gettail,			"gettail" },
	{ ArraySpecApiType_max,				NULL },
};

str_t ArraySpecApiTypeStr(ArraySpecApiType type)
{
	struct ArraySpecApiTypeMap *i;
	for (i = ArraySpecApiTypeMap; i->type != ArraySpecApiType_max; i++)
		if (i->type == type) break;
	return i->name;
}

ArraySpecApiType ArraySpecApiTypeFromStr(str_t str)
{
	struct ArraySpecApiTypeMap *i;
	for (i = api_map; i->type != ArraySpecApiType_max; i++)
		if (strcmp(i->name, str) == 0) break;
	return i->type;
}

void PublishArraySpec_dump(PublishArraySpec *p, int tab)
{
	int i;
	char buf[1024];
	if (!p) return;
	Dz1Thread_tprintf(tab, "type = %s%s\n", p->name, p->createNeedCmp ? "(comparable)" : "");
	Dz1Thread_tprintf(tab, "travel function type = %s\n", p->travelFuncCast);
	for (i = 0; i < ArraySpecApiType_max; i++)
	{
		Dz1Thread_tprintf(tab + 1, "%s api = %s\n", ArraySpecApiTypeStr((ArraySpecApiType)i), p->apiName(p, buf, (ArraySpecApiType)i, "*p"));
	}
}

///////////////////////////////////////////////////////////////////////////////
// Native Type Spec
///////////////////////////////////////////////////////////////////////////////
static void NativeTypeSpec_del(NativeTypeSpec *p)
{
	if (!p) return;
	if (p->name) Dz1Str_del(p->name);
	if (p->native) Dz1Str_del(p->native);
	if (p->prefix) Dz1Str_del(p->prefix);
	Dz1Free(p);
}

static void NativeTypeSpec_delAndSetNull(void *ptr)
{
	NativeTypeSpec **p = (NativeTypeSpec **)ptr;
	NativeTypeSpec_del(*p); *p = NULL;
}

//static NativeTypeSpec *NativeTypeSpec_new(str_t name, str_t native, bool_t isPointer, str_t prefix, u32_t attr_flag, Dz1Error *err)
static NativeTypeSpec *NativeTypeSpec_new(str_t name, str_t native, NativeStorage storage, str_t prefix, u32_t attr_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	NativeTypeSpec *ret = (NativeTypeSpec *)Dz1Calloc(sizeof(NativeTypeSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(NativeTypeSpec_delAndSetNull, (void *)&ret);
		if ((ret->name = Dz1Str_dup(name, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->native = Dz1Str_dup(native, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->prefix = Dz1Str_dup(prefix, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->attr_flag = attr_flag;
			ret->storage = storage;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (NativeTypeSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static void NativeTypeSpec_dump(NativeTypeSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab, "%s as %s native type %s ", p->name, NativeStorageStr(p->storage));
	Dz1Thread_printf("with api prefix : %s\n", p->prefix);
}

static int NativeTypeSpec_cmp(NativeTypeSpec *a, NativeTypeSpec *b)
{
	int la = (int)strlen(a->name), lb = (int)strlen(b->name);
	int ret = la - lb;
	if (ret == 0) ret = strcmp(a->name, b->name);
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Spec Method
///////////////////////////////////////////////////////////////////////////////
// bool_t				 (*regPrimitive)(struct PublishSpec *p, str_t name, str_t native, bool_t isPointer, str_t prefix, u32_t attr_flag, Dz1Error *err);
static bool_t PublishSpec_regPrimitive(PublishSpec *p, str_t name, str_t native, bool_t isPointer, str_t prefix, u32_t attr_flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	NativeTypeSpec *e = NativeTypeSpec_new(name, native, isPointer, prefix, attr_flag, errp);
	if (e == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)NativeTypeSpec_del, (void *)e);

		if ((*errp = Dz1AATree_insert(p->primitives, e)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)NativeTypeSpec_del, (void *)e);
	}
//	return err;
	return errp->code == 0 ? TRUE : FALSE;
}

static NativeTypeSpec *PublishSpec_findPrimitive(PublishSpec *p, str_t name)
{
	NativeTypeSpec key = { name };
	return (NativeTypeSpec *)Dz1AATree_find(p->primitives, (void *)&key);
}

static Dz1Error PublishSpec_regInc(void *inc, str_t fn)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((fn = Dz1Str_dup(fn, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1Str_del, (void *)fn);
		if ((err = Dz1Fifo_push(inc, fn)).code) ERR_OUT(&err);
		pthread_cleanup_pop(err.code); // ((Dz1CancelFunc)Dz1Str_del, (void *)fn);
	}
	return err;
}

static Dz1Error PublishSpec_regHeaderInc(PublishSpec *p, str_t fn) { return PublishSpec_regInc(p->headerInclude, fn); }
static Dz1Error PublishSpec_regSourceInc(PublishSpec *p, str_t fn) { return PublishSpec_regInc(p->sourceInclude, fn); }

PublishSpec *PublishSpec_new(	bool_t pthread,

								PublishBasicSpec	*base,

								PublishErrorSpec	*error,
								PublishCastSpec		*cast,
								PublishMemFuncSpec	*mem,

								PublishPostFix		*postFix,

								Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishSpec *ret = (PublishSpec *)Dz1Calloc(sizeof(PublishSpec), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(PublishSpec_delAndSetNull, (void *)&ret);

		if ((ret->primitives = Dz1AATree_new((Dz1CmpFunc)NativeTypeSpec_cmp, (Dz1DelFunc)NativeTypeSpec_del, (Dz1DumpFunc)NativeTypeSpec_dump, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->headerInclude = Dz1Fifo_new((Dz1DelFunc)Dz1Str_del, (Dz1DumpFunc)Dz1Str_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else if ((ret->sourceInclude = Dz1Fifo_new((Dz1DelFunc)Dz1Str_del, (Dz1DumpFunc)Dz1Str_dump, 0, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->pthread = pthread;

			ret->base = base;
			ret->error = error;
			ret->cast = cast;
			ret->mem = mem;
			ret->postFix = postFix;

			ret->regPrimitive = PublishSpec_regPrimitive;
			ret->findPrimitive = PublishSpec_findPrimitive;
			ret->regHeaderInc = PublishSpec_regHeaderInc;
			ret->regSourceInc = PublishSpec_regSourceInc;
		}

		pthread_cleanup_pop(errp->code); // (PublishSpec_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void PublishSpec_del(PublishSpec *p)
{
	if (!p) return;
	if (p->base) PublishBasicSpec_del(p->base);
	if (p->error) PublishErrorSpec_del(p->error);
	if (p->cast) PublishCastSpec_del(p->cast);
	if (p->mem) PublishMemFuncSpec_del(p->mem);
	if (p->postFix) PublishPostFix_del(p->postFix);
	if (p->arraySpec[ArrayType_normal]) PublishArraySpec_del(p->arraySpec[ArrayType_normal]);
	if (p->arraySpec[ArrayType_ordered]) PublishArraySpec_del(p->arraySpec[ArrayType_ordered]);
	if (p->arraySpec[ArrayType_unique]) PublishArraySpec_del(p->arraySpec[ArrayType_unique]);
	if (p->primitives) Dz1AATree_del(p->primitives);
	if (p->headerInclude) Dz1Fifo_del(p->headerInclude);
	if (p->sourceInclude) Dz1Fifo_del(p->sourceInclude);
	Dz1Free(p);
}

void PublishSpec_dump(PublishSpec *p, int tab)
{
	if (!p) return;
	Dz1Thread_tprintf(tab++, "Publish Spec {\n");

	Dz1Thread_tprintf(tab, "pthread = %s\n", p->pthread ? "yes" : "no");
	if (p->base)
	{
		Dz1Thread_tprintf(tab++, "Basic Spec = {\n");
		PublishBasicSpec_dump(p->base, tab + 1);
		Dz1Thread_tprintf(--tab, "}\n");
	}
	if (p->error)
	{
		Dz1Thread_tprintf(tab++, "Error Spec = {\n");
		PublishErrorSpec_dump(p->error, tab + 1);
		Dz1Thread_tprintf(--tab, "}\n");
	}
	if (p->cast)
	{
		Dz1Thread_tprintf(tab++, "Casting Spec = {\n");
		PublishCastSpec_dump(p->cast, tab + 1);
		Dz1Thread_tprintf(--tab, "}\n");
	}
	if (p->mem)
	{
		Dz1Thread_tprintf(tab++, "Memory API Spec = {\n");
		PublishMemFuncSpec_dump(p->mem, tab + 1);
		Dz1Thread_tprintf(--tab, "}\n");
	}
	if (p->postFix)
	{
		Dz1Thread_tprintf(tab++, "Post Fix Spec = {\n");
		PublishPostFix_dump(p->postFix, tab + 1);
		Dz1Thread_tprintf(--tab, "}\n");
	}

	if (p->arraySpec[ArrayType_normal])
	{
		Dz1Thread_tprintf(tab++, "Array Spec = {\n");
		PublishArraySpec_dump(p->arraySpec[ArrayType_normal], tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}

	if (p->arraySpec[ArrayType_ordered])
	{
		Dz1Thread_tprintf(tab++, "Table Spec = {\n");
		PublishArraySpec_dump(p->arraySpec[ArrayType_ordered], tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}

	if (p->arraySpec[ArrayType_unique])
	{
		Dz1Thread_tprintf(tab++, "Table Spec = {\n");
		PublishArraySpec_dump(p->arraySpec[ArrayType_unique], tab);
		Dz1Thread_tprintf(--tab, "}\n");
	}

	Dz1Thread_tprintf(tab++, "Primitives = {\n");
	Dz1AATree_dump(p->primitives, tab);
	Dz1Thread_tprintf(--tab, "}\n");

	Dz1Thread_tprintf(tab++, "Header Includes = {\n");
	Dz1Fifo_dump(p->headerInclude, tab);
	Dz1Thread_tprintf(--tab, "}\n");

	Dz1Thread_tprintf(tab++, "Source Includes = {\n");
	Dz1Fifo_dump(p->sourceInclude, tab);
	Dz1Thread_tprintf(--tab, "}\n");

	Dz1Thread_tprintf(--tab, "}\n");
}


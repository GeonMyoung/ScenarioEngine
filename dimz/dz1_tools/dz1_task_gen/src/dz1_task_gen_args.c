////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_task_gen_args.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1GenTextMode
static struct Dz1GenTextModeMapA
{
	str_t str;
	Dz1GenTextMode v;
} Dz1GenTextModeMapA[] =
{
	{ (char *)"DOS", Dz1GenTextMode_DOS },
	{ (char *)"UNIX", Dz1GenTextMode_UNIX },
	{ NULL, Dz1GenTextMode_max }
};

str_t Dz1GenTextModeStrA(Dz1GenTextMode v)
{
	struct Dz1GenTextModeMapA *i = NULL;
	for (i = Dz1GenTextModeMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GenTextMode Dz1GenTextModeFromStrA(str_t str)
{
	struct Dz1GenTextModeMapA *i = NULL;
	for (i = Dz1GenTextModeMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GenTextMode_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GenTextModeMapW
{
	wstr_t str;
	Dz1GenTextMode v;
} Dz1GenTextModeMapW[] =
{
	{ (wchar_t *)L"DOS", Dz1GenTextMode_DOS },
	{ (wchar_t *)L"UNIX", Dz1GenTextMode_UNIX },
	{ NULL, Dz1GenTextMode_max }
};

wstr_t Dz1GenTextModeStrW(Dz1GenTextMode v)
{
	struct Dz1GenTextModeMapW *i = NULL;
	for (i = Dz1GenTextModeMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GenTextMode Dz1GenTextModeFromStrW(wstr_t str)
{
	struct Dz1GenTextModeMapW *i = NULL;
	for (i = Dz1GenTextModeMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GenTextMode_max;
}
#endif // UNIX_SYSTEM

Dz1GenTextMode *Dz1GenTextMode_new(Dz1GenTextMode *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GenTextMode *__internal_ret = (Dz1GenTextMode *)Dz1Calloc(sizeof(Dz1GenTextMode), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1GenTextMode
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1GenTarget
static struct Dz1GenTargetMapA
{
	str_t str;
	Dz1GenTarget v;
} Dz1GenTargetMapA[] =
{
	{ (char *)"StaticLibrary", Dz1GenTarget_StaticLibrary },
	{ (char *)"Task", Dz1GenTarget_Task },
	{ NULL, Dz1GenTarget_max }
};

str_t Dz1GenTargetStrA(Dz1GenTarget v)
{
	struct Dz1GenTargetMapA *i = NULL;
	for (i = Dz1GenTargetMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GenTarget Dz1GenTargetFromStrA(str_t str)
{
	struct Dz1GenTargetMapA *i = NULL;
	for (i = Dz1GenTargetMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1GenTarget_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1GenTargetMapW
{
	wstr_t str;
	Dz1GenTarget v;
} Dz1GenTargetMapW[] =
{
	{ (wchar_t *)L"StaticLibrary", Dz1GenTarget_StaticLibrary },
	{ (wchar_t *)L"Task", Dz1GenTarget_Task },
	{ NULL, Dz1GenTarget_max }
};

wstr_t Dz1GenTargetStrW(Dz1GenTarget v)
{
	struct Dz1GenTargetMapW *i = NULL;
	for (i = Dz1GenTargetMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1GenTarget Dz1GenTargetFromStrW(wstr_t str)
{
	struct Dz1GenTargetMapW *i = NULL;
	for (i = Dz1GenTargetMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1GenTarget_max;
}
#endif // UNIX_SYSTEM

Dz1GenTarget *Dz1GenTarget_new(Dz1GenTarget *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1GenTarget *__internal_ret = (Dz1GenTarget *)Dz1Calloc(sizeof(Dz1GenTarget), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1GenTarget
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// ProjectVcConf
static struct ProjectVcConfMapA
{
	str_t str;
	ProjectVcConf v;
} ProjectVcConfMapA[] =
{
	{ (char *)"Debug", ProjectVcConf_Debug },
	{ (char *)"DebugDLL", ProjectVcConf_DebugDLL },
	{ (char *)"Release", ProjectVcConf_Release },
	{ (char *)"ReleaseDLL", ProjectVcConf_ReleaseDLL },
	{ NULL, ProjectVcConf_max }
};

str_t ProjectVcConfStrA(ProjectVcConf v)
{
	struct ProjectVcConfMapA *i = NULL;
	for (i = ProjectVcConfMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ProjectVcConf ProjectVcConfFromStrA(str_t str)
{
	struct ProjectVcConfMapA *i = NULL;
	for (i = ProjectVcConfMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return ProjectVcConf_max;
}
#ifndef UNIX_SYSTEM
static struct ProjectVcConfMapW
{
	wstr_t str;
	ProjectVcConf v;
} ProjectVcConfMapW[] =
{
	{ (wchar_t *)L"Debug", ProjectVcConf_Debug },
	{ (wchar_t *)L"DebugDLL", ProjectVcConf_DebugDLL },
	{ (wchar_t *)L"Release", ProjectVcConf_Release },
	{ (wchar_t *)L"ReleaseDLL", ProjectVcConf_ReleaseDLL },
	{ NULL, ProjectVcConf_max }
};

wstr_t ProjectVcConfStrW(ProjectVcConf v)
{
	struct ProjectVcConfMapW *i = NULL;
	for (i = ProjectVcConfMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

ProjectVcConf ProjectVcConfFromStrW(wstr_t str)
{
	struct ProjectVcConfMapW *i = NULL;
	for (i = ProjectVcConfMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return ProjectVcConf_max;
}
#endif // UNIX_SYSTEM

ProjectVcConf *ProjectVcConf_new(ProjectVcConf *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	ProjectVcConf *__internal_ret = (ProjectVcConf *)Dz1Calloc(sizeof(ProjectVcConf), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// ProjectVcConf
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1TaskGenEndian
static struct Dz1TaskGenEndianMapA
{
	str_t str;
	Dz1TaskGenEndian v;
} Dz1TaskGenEndianMapA[] =
{
	{ (char *)"Little", Dz1TaskGenEndian_Little },
	{ (char *)"Big", Dz1TaskGenEndian_Big },
	{ NULL, Dz1TaskGenEndian_max }
};

str_t Dz1TaskGenEndianStrA(Dz1TaskGenEndian v)
{
	struct Dz1TaskGenEndianMapA *i = NULL;
	for (i = Dz1TaskGenEndianMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TaskGenEndian Dz1TaskGenEndianFromStrA(str_t str)
{
	struct Dz1TaskGenEndianMapA *i = NULL;
	for (i = Dz1TaskGenEndianMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return Dz1TaskGenEndian_max;
}
#ifndef UNIX_SYSTEM
static struct Dz1TaskGenEndianMapW
{
	wstr_t str;
	Dz1TaskGenEndian v;
} Dz1TaskGenEndianMapW[] =
{
	{ (wchar_t *)L"Little", Dz1TaskGenEndian_Little },
	{ (wchar_t *)L"Big", Dz1TaskGenEndian_Big },
	{ NULL, Dz1TaskGenEndian_max }
};

wstr_t Dz1TaskGenEndianStrW(Dz1TaskGenEndian v)
{
	struct Dz1TaskGenEndianMapW *i = NULL;
	for (i = Dz1TaskGenEndianMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

Dz1TaskGenEndian Dz1TaskGenEndianFromStrW(wstr_t str)
{
	struct Dz1TaskGenEndianMapW *i = NULL;
	for (i = Dz1TaskGenEndianMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return Dz1TaskGenEndian_max;
}
#endif // UNIX_SYSTEM

Dz1TaskGenEndian *Dz1TaskGenEndian_new(Dz1TaskGenEndian *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	Dz1TaskGenEndian *__internal_ret = (Dz1TaskGenEndian *)Dz1Calloc(sizeof(Dz1TaskGenEndian), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// Dz1TaskGenEndian
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2Naming
static struct GenArgs2NamingMapA
{
	str_t str;
	GenArgs2Naming v;
} GenArgs2NamingMapA[] =
{
	{ (char *)"canonical", GenArgs2Naming_canonical },
	{ (char *)"underscore", GenArgs2Naming_underscore },
	{ NULL, GenArgs2Naming_max }
};

str_t GenArgs2NamingStrA(GenArgs2Naming v)
{
	struct GenArgs2NamingMapA *i = NULL;
	for (i = GenArgs2NamingMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2Naming GenArgs2NamingFromStrA(str_t str)
{
	struct GenArgs2NamingMapA *i = NULL;
	for (i = GenArgs2NamingMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GenArgs2Naming_max;
}
#ifndef UNIX_SYSTEM
static struct GenArgs2NamingMapW
{
	wstr_t str;
	GenArgs2Naming v;
} GenArgs2NamingMapW[] =
{
	{ (wchar_t *)L"canonical", GenArgs2Naming_canonical },
	{ (wchar_t *)L"underscore", GenArgs2Naming_underscore },
	{ NULL, GenArgs2Naming_max }
};

wstr_t GenArgs2NamingStrW(GenArgs2Naming v)
{
	struct GenArgs2NamingMapW *i = NULL;
	for (i = GenArgs2NamingMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2Naming GenArgs2NamingFromStrW(wstr_t str)
{
	struct GenArgs2NamingMapW *i = NULL;
	for (i = GenArgs2NamingMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GenArgs2Naming_max;
}
#endif // UNIX_SYSTEM

GenArgs2Naming *GenArgs2Naming_new(GenArgs2Naming *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2Naming *__internal_ret = (GenArgs2Naming *)Dz1Calloc(sizeof(GenArgs2Naming), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GenArgs2Naming
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioVer
static struct GenArgs2VisualStudioVerMapA
{
	str_t str;
	GenArgs2VisualStudioVer v;
} GenArgs2VisualStudioVerMapA[] =
{
	{ (char *)"vc71", GenArgs2VisualStudioVer_vc71 },
	{ (char *)"vc90", GenArgs2VisualStudioVer_vc90 },
	{ (char *)"vs2015", GenArgs2VisualStudioVer_vs2015 },
	{ (char *)"vs2017", GenArgs2VisualStudioVer_vs2017 },
	{ (char *)"vs2019", GenArgs2VisualStudioVer_vs2019 },
	{ (char *)"vs2022", GenArgs2VisualStudioVer_vs2022 },
	{ NULL, GenArgs2VisualStudioVer_max }
};

str_t GenArgs2VisualStudioVerStrA(GenArgs2VisualStudioVer v)
{
	struct GenArgs2VisualStudioVerMapA *i = NULL;
	for (i = GenArgs2VisualStudioVerMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2VisualStudioVer GenArgs2VisualStudioVerFromStrA(str_t str)
{
	struct GenArgs2VisualStudioVerMapA *i = NULL;
	for (i = GenArgs2VisualStudioVerMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GenArgs2VisualStudioVer_max;
}
#ifndef UNIX_SYSTEM
static struct GenArgs2VisualStudioVerMapW
{
	wstr_t str;
	GenArgs2VisualStudioVer v;
} GenArgs2VisualStudioVerMapW[] =
{
	{ (wchar_t *)L"vc71", GenArgs2VisualStudioVer_vc71 },
	{ (wchar_t *)L"vc90", GenArgs2VisualStudioVer_vc90 },
	{ (wchar_t *)L"vs2015", GenArgs2VisualStudioVer_vs2015 },
	{ (wchar_t *)L"vs2017", GenArgs2VisualStudioVer_vs2017 },
	{ (wchar_t *)L"vs2019", GenArgs2VisualStudioVer_vs2019 },
	{ (wchar_t *)L"vs2022", GenArgs2VisualStudioVer_vs2022 },
	{ NULL, GenArgs2VisualStudioVer_max }
};

wstr_t GenArgs2VisualStudioVerStrW(GenArgs2VisualStudioVer v)
{
	struct GenArgs2VisualStudioVerMapW *i = NULL;
	for (i = GenArgs2VisualStudioVerMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2VisualStudioVer GenArgs2VisualStudioVerFromStrW(wstr_t str)
{
	struct GenArgs2VisualStudioVerMapW *i = NULL;
	for (i = GenArgs2VisualStudioVerMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GenArgs2VisualStudioVer_max;
}
#endif // UNIX_SYSTEM

GenArgs2VisualStudioVer *GenArgs2VisualStudioVer_new(GenArgs2VisualStudioVer *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudioVer *__internal_ret = (GenArgs2VisualStudioVer *)Dz1Calloc(sizeof(GenArgs2VisualStudioVer), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GenArgs2VisualStudioVer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioVerSupport
static struct GenArgs2VisualStudioVerSupportMapA
{
	str_t str;
	GenArgs2VisualStudioVerSupport v;
} GenArgs2VisualStudioVerSupportMapA[] =
{
	{ (char *)"vc90", GenArgs2VisualStudioVerSupport_vc90 },
	{ (char *)"vs2022", GenArgs2VisualStudioVerSupport_vs2022 },
	{ NULL, GenArgs2VisualStudioVerSupport_max }
};

str_t GenArgs2VisualStudioVerSupportStrA(GenArgs2VisualStudioVerSupport v)
{
	struct GenArgs2VisualStudioVerSupportMapA *i = NULL;
	for (i = GenArgs2VisualStudioVerSupportMapA; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2VisualStudioVerSupport GenArgs2VisualStudioVerSupportFromStrA(str_t str)
{
	struct GenArgs2VisualStudioVerSupportMapA *i = NULL;
	for (i = GenArgs2VisualStudioVerSupportMapA; i->str; i++)
		if (dz1_built_in_str_cmp(i->str, str) == 0) return i->v;
	return GenArgs2VisualStudioVerSupport_max;
}
#ifndef UNIX_SYSTEM
static struct GenArgs2VisualStudioVerSupportMapW
{
	wstr_t str;
	GenArgs2VisualStudioVerSupport v;
} GenArgs2VisualStudioVerSupportMapW[] =
{
	{ (wchar_t *)L"vc90", GenArgs2VisualStudioVerSupport_vc90 },
	{ (wchar_t *)L"vs2022", GenArgs2VisualStudioVerSupport_vs2022 },
	{ NULL, GenArgs2VisualStudioVerSupport_max }
};

wstr_t GenArgs2VisualStudioVerSupportStrW(GenArgs2VisualStudioVerSupport v)
{
	struct GenArgs2VisualStudioVerSupportMapW *i = NULL;
	for (i = GenArgs2VisualStudioVerSupportMapW; i->str; i++)
		if (i->v == v) return i->str;
	return NULL;
}

GenArgs2VisualStudioVerSupport GenArgs2VisualStudioVerSupportFromStrW(wstr_t str)
{
	struct GenArgs2VisualStudioVerSupportMapW *i = NULL;
	for (i = GenArgs2VisualStudioVerSupportMapW; i->str; i++)
		if (dz1_built_in_wstr_cmp(i->str, str) == 0) return i->v;
	return GenArgs2VisualStudioVerSupport_max;
}
#endif // UNIX_SYSTEM

GenArgs2VisualStudioVerSupport *GenArgs2VisualStudioVerSupport_new(GenArgs2VisualStudioVerSupport *src, Dz1Error *err){
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudioVerSupport *__internal_ret = (GenArgs2VisualStudioVerSupport *)Dz1Calloc(sizeof(GenArgs2VisualStudioVerSupport), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		*__internal_ret = *src;
		ERR_CLEAR(errp);
	}
	return __internal_ret;
}
// GenArgs2VisualStudioVerSupport
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioEntry
GenArgs2VisualStudioEntry *GenArgs2VisualStudioEntry_new(GenArgs2VisualStudioVer ver, 
														 Dz1Str middle_path, 
														 Dz1Str proj_file_name, 
														 Dz1Str proj_guid, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudioEntry *__internal_ret = (GenArgs2VisualStudioEntry *)Dz1Calloc(sizeof(GenArgs2VisualStudioEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (middle_path && (__internal_ret->middle_path = Dz1Str_clone(middle_path, errp)) == NULL) ERR_OUT(errp);
		else if (proj_file_name && (__internal_ret->proj_file_name = Dz1Str_clone(proj_file_name, errp)) == NULL) ERR_OUT(errp);
		else if (proj_guid && (__internal_ret->proj_guid = Dz1Str_clone(proj_guid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->ver = ver;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GenArgs2VisualStudioEntry_copy(GenArgs2VisualStudioEntry *dst, GenArgs2VisualStudioEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->middle_path && (dst->middle_path = Dz1Str_clone(src->middle_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->proj_file_name && (dst->proj_file_name = Dz1Str_clone(src->proj_file_name, errp)) == NULL) ERR_OUT(errp);
	else if (src->proj_guid && (dst->proj_guid = Dz1Str_clone(src->proj_guid, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->ver = src->ver;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GenArgs2VisualStudioEntry *GenArgs2VisualStudioEntry_clone(GenArgs2VisualStudioEntry *src, Dz1Error *err)
{
	GenArgs2VisualStudioEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GenArgs2VisualStudioEntry *)Dz1Calloc(sizeof(GenArgs2VisualStudioEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&dst);
		if (GenArgs2VisualStudioEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GenArgs2VisualStudioEntry_purge(GenArgs2VisualStudioEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->middle_path);
	Dz1Str_del(p->proj_file_name);
	Dz1Str_del(p->proj_guid);
}

void GenArgs2VisualStudioEntry_del(GenArgs2VisualStudioEntry *p)
{
	if (p == NULL) return;
	GenArgs2VisualStudioEntry_purge(p);
	Dz1Free(p);
}

void GenArgs2VisualStudioEntry_dump(GenArgs2VisualStudioEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("ver = %s(%d)\n"), GenArgs2VisualStudioVerStr(p->ver), p->ver);
		Dz1Thread_tprintf(tab, Dz1T("middle_path = ")); Dz1Str_dump(p->middle_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("proj_file_name = ")); Dz1Str_dump(p->proj_file_name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("proj_guid = ")); Dz1Str_dump(p->proj_guid, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int GenArgs2VisualStudioEntry_cmp(GenArgs2VisualStudioEntry *a, GenArgs2VisualStudioEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = (int)(a->ver - b->ver)) != 0) { }
	return ret;
}
// GenArgs2VisualStudioEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudioList
static Dz1Error GenArgs2VisualStudioList_add(GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *data)
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

static bool_t GenArgs2VisualStudioList_remove(GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static GenArgs2VisualStudioEntry *GenArgs2VisualStudioList_extract(GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key)
{
	return (GenArgs2VisualStudioEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct GenArgs2VisualStudioListMkArrArg
{
	GenArgs2VisualStudioEntry **arr;
	unsigned int idx;
} GenArgs2VisualStudioListMkArrArg;

static Dz1Error _GenArgs2VisualStudioList_get_array(void *ptr, GenArgs2VisualStudioEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2VisualStudioListMkArrArg *arg = (GenArgs2VisualStudioListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GenArgs2VisualStudioEntry **GenArgs2VisualStudioList_get_array(GenArgs2VisualStudioList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GenArgs2VisualStudioEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GenArgs2VisualStudioEntry **)Dz1Calloc(sizeof(GenArgs2VisualStudioEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GenArgs2VisualStudioListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GenArgs2VisualStudioList_get_array, (void *)&arg);
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

static Dz1Error GenArgs2VisualStudioList_travelForward(GenArgs2VisualStudioList *p, Dz1Error (*func)(void *ptr, GenArgs2VisualStudioEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error GenArgs2VisualStudioList_travelBackward(GenArgs2VisualStudioList *p, Dz1Error (*func)(void *ptr, GenArgs2VisualStudioEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static GenArgs2VisualStudioEntry *GenArgs2VisualStudioList_find(GenArgs2VisualStudioList *p, GenArgs2VisualStudioEntry *key)
{
	return (GenArgs2VisualStudioEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int GenArgs2VisualStudioList_count(GenArgs2VisualStudioList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

GenArgs2VisualStudioList *GenArgs2VisualStudioList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudioList *ret = (GenArgs2VisualStudioList *)Dz1Calloc(sizeof(GenArgs2VisualStudioList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)GenArgs2VisualStudioEntry_cmp,
				(Dz1DelFunc)GenArgs2VisualStudioEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GenArgs2VisualStudioList_count;
			ret->travel = GenArgs2VisualStudioList_travelForward;
			ret->travelForward = GenArgs2VisualStudioList_travelForward;
			ret->travelBackward = GenArgs2VisualStudioList_travelBackward;
			ret->get_array = GenArgs2VisualStudioList_get_array;
			ret->add = GenArgs2VisualStudioList_add;
			ret->remove = GenArgs2VisualStudioList_remove;
			ret->find = GenArgs2VisualStudioList_find;
			ret->extract = GenArgs2VisualStudioList_extract;
			ret->cmp = GenArgs2VisualStudioEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudioList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GenArgs2VisualStudioList_clone(void *ptr, GenArgs2VisualStudioEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2VisualStudioList *p = (GenArgs2VisualStudioList *)ptr;
	GenArgs2VisualStudioEntry *cloned = GenArgs2VisualStudioEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GenArgs2VisualStudioList *GenArgs2VisualStudioList_clone(GenArgs2VisualStudioList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudioList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GenArgs2VisualStudioList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_GenArgs2VisualStudioList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudioList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GenArgs2VisualStudioList_purge(GenArgs2VisualStudioList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void GenArgs2VisualStudioList_del(GenArgs2VisualStudioList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GenArgs2VisualStudioList_dump(void *ptr, GenArgs2VisualStudioEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GenArgs2VisualStudioEntry_dump(p, tab);
	return err;
}

void GenArgs2VisualStudioList_dump(GenArgs2VisualStudioList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GenArgs2VisualStudioList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GenArgs2VisualStudioList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryEntry
GenArgs2LibraryEntry *GenArgs2LibraryEntry_new(Dz1Str name, 
											   Dz1Str path_root_abs, 
											   u32_t order, 
											   Dz1Str root2inc_path, 
											   Dz1Str root2lib_path, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryEntry *__internal_ret = (GenArgs2LibraryEntry *)Dz1Calloc(sizeof(GenArgs2LibraryEntry), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenArgs2LibraryEntry_delAndSetNull, (void *)&__internal_ret);
		
		if (name && (__internal_ret->name = Dz1Str_clone(name, errp)) == NULL) ERR_OUT(errp);
		else if (path_root_abs && (__internal_ret->path_root_abs = Dz1Str_clone(path_root_abs, errp)) == NULL) ERR_OUT(errp);
		else if (root2inc_path && (__internal_ret->root2inc_path = Dz1Str_clone(root2inc_path, errp)) == NULL) ERR_OUT(errp);
		else if (root2lib_path && (__internal_ret->root2lib_path = Dz1Str_clone(root2lib_path, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->projects = GenArgs2VisualStudioList_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->order = order;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryEntry_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GenArgs2LibraryEntry_copy(GenArgs2LibraryEntry *dst, GenArgs2LibraryEntry *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->name && (dst->name = Dz1Str_clone(src->name, errp)) == NULL) ERR_OUT(errp);
	else if (src->path_root_abs && (dst->path_root_abs = Dz1Str_clone(src->path_root_abs, errp)) == NULL) ERR_OUT(errp);
	else if (src->root2inc_path && (dst->root2inc_path = Dz1Str_clone(src->root2inc_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->root2lib_path && (dst->root2lib_path = Dz1Str_clone(src->root2lib_path, errp)) == NULL) ERR_OUT(errp);
	else if (src->projects && (dst->projects = GenArgs2VisualStudioList_clone(src->projects, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->order = src->order;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GenArgs2LibraryEntry *GenArgs2LibraryEntry_clone(GenArgs2LibraryEntry *src, Dz1Error *err)
{
	GenArgs2LibraryEntry *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GenArgs2LibraryEntry *)Dz1Calloc(sizeof(GenArgs2LibraryEntry), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GenArgs2LibraryEntry_delAndSetNull, (void *)&dst);
		if (GenArgs2LibraryEntry_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryEntry_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GenArgs2LibraryEntry_purge(GenArgs2LibraryEntry *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->name);
	Dz1Str_del(p->path_root_abs);
	Dz1Str_del(p->root2inc_path);
	Dz1Str_del(p->root2lib_path);
	GenArgs2VisualStudioList_del(p->projects);
}

void GenArgs2LibraryEntry_del(GenArgs2LibraryEntry *p)
{
	if (p == NULL) return;
	GenArgs2LibraryEntry_purge(p);
	Dz1Free(p);
}

void GenArgs2LibraryEntry_dump(GenArgs2LibraryEntry *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("name = ")); Dz1Str_dump(p->name, tab); 
		Dz1Thread_tprintf(tab, Dz1T("path_root_abs = ")); Dz1Str_dump(p->path_root_abs, tab); 
		Dz1Thread_tprintf(tab, Dz1T("order = ")); Dz1u32_dump(&p->order, tab); 
		Dz1Thread_tprintf(tab, Dz1T("root2inc_path = ")); Dz1Str_dump(p->root2inc_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("root2lib_path = ")); Dz1Str_dump(p->root2lib_path, tab); 
		Dz1Thread_tprintf(tab, Dz1T("projects = ")); GenArgs2VisualStudioList_dump(p->projects, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
int GenArgs2LibraryEntry_cmp(GenArgs2LibraryEntry *a, GenArgs2LibraryEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) { }
	else if (a == NULL /* && b != NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if (a->name == NULL && b->name == NULL) ret = 0;
	else if (a->name == NULL /*&& b->name != NULL*/) ret = -1;
	else if (/*a->name != NULL &&*/ b->name == NULL) ret = 1;
	else if ((ret = Dz1Str_cmp(a->name, b->name)) != 0) { }
	return ret;
}
// GenArgs2LibraryEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryList
static Dz1Error GenArgs2LibraryList_add(GenArgs2LibraryList *p, GenArgs2LibraryEntry *data)
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

static bool_t GenArgs2LibraryList_remove(GenArgs2LibraryList *p, GenArgs2LibraryEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static GenArgs2LibraryEntry *GenArgs2LibraryList_extract(GenArgs2LibraryList *p, GenArgs2LibraryEntry *key)
{
	return (GenArgs2LibraryEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct GenArgs2LibraryListMkArrArg
{
	GenArgs2LibraryEntry **arr;
	unsigned int idx;
} GenArgs2LibraryListMkArrArg;

static Dz1Error _GenArgs2LibraryList_get_array(void *ptr, GenArgs2LibraryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2LibraryListMkArrArg *arg = (GenArgs2LibraryListMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GenArgs2LibraryEntry **GenArgs2LibraryList_get_array(GenArgs2LibraryList *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GenArgs2LibraryEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GenArgs2LibraryEntry **)Dz1Calloc(sizeof(GenArgs2LibraryEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GenArgs2LibraryListMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GenArgs2LibraryList_get_array, (void *)&arg);
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

static Dz1Error GenArgs2LibraryList_travelForward(GenArgs2LibraryList *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error GenArgs2LibraryList_travelBackward(GenArgs2LibraryList *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static GenArgs2LibraryEntry *GenArgs2LibraryList_find(GenArgs2LibraryList *p, GenArgs2LibraryEntry *key)
{
	return (GenArgs2LibraryEntry *)Dz1AATree_find(p->storage, key);
}

static unsigned int GenArgs2LibraryList_count(GenArgs2LibraryList *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

GenArgs2LibraryList *GenArgs2LibraryList_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryList *ret = (GenArgs2LibraryList *)Dz1Calloc(sizeof(GenArgs2LibraryList), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2LibraryList_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new(
				(Dz1CmpFunc)GenArgs2LibraryEntry_cmp,
				(Dz1DelFunc)GenArgs2LibraryEntry_del,
				NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GenArgs2LibraryList_count;
			ret->travel = GenArgs2LibraryList_travelForward;
			ret->travelForward = GenArgs2LibraryList_travelForward;
			ret->travelBackward = GenArgs2LibraryList_travelBackward;
			ret->get_array = GenArgs2LibraryList_get_array;
			ret->add = GenArgs2LibraryList_add;
			ret->remove = GenArgs2LibraryList_remove;
			ret->find = GenArgs2LibraryList_find;
			ret->extract = GenArgs2LibraryList_extract;
			ret->cmp = GenArgs2LibraryEntry_cmp;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GenArgs2LibraryList_clone(void *ptr, GenArgs2LibraryEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2LibraryList *p = (GenArgs2LibraryList *)ptr;
	GenArgs2LibraryEntry *cloned = GenArgs2LibraryEntry_clone(data, &err); // normal
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GenArgs2LibraryList *GenArgs2LibraryList_clone(GenArgs2LibraryList *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryList *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GenArgs2LibraryList_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2LibraryList_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_GenArgs2LibraryList_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryList_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GenArgs2LibraryList_purge(GenArgs2LibraryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void GenArgs2LibraryList_del(GenArgs2LibraryList *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GenArgs2LibraryList_dump(void *ptr, GenArgs2LibraryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GenArgs2LibraryEntry_dump(p, tab);
	return err;
}

void GenArgs2LibraryList_dump(GenArgs2LibraryList *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GenArgs2LibraryList_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GenArgs2LibraryList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryRefIndex
static Dz1Error GenArgs2LibraryRefIndex_add(GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *data)
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

static bool_t GenArgs2LibraryRefIndex_remove(GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key)
{
	return Dz1AATree_remove(p->storage, key);
}

static GenArgs2LibraryEntry *GenArgs2LibraryRefIndex_extract(GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key)
{
	return (GenArgs2LibraryEntry *)Dz1AATree_extract(p->storage, key);
}

typedef struct GenArgs2LibraryRefIndexMkArrArg
{
	GenArgs2LibraryEntry **arr;
	unsigned int idx;
} GenArgs2LibraryRefIndexMkArrArg;

static Dz1Error _GenArgs2LibraryRefIndex_get_array(void *ptr, GenArgs2LibraryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2LibraryRefIndexMkArrArg *arg = (GenArgs2LibraryRefIndexMkArrArg *)ptr;
	arg->arr[arg->idx++] = p;
	return err;
}

static GenArgs2LibraryEntry **GenArgs2LibraryRefIndex_get_array(GenArgs2LibraryRefIndex *p, unsigned int *ret_cnt, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err == NULL ? &_err : err;
	GenArgs2LibraryEntry **ret = NULL;
	unsigned int cnt = 0;
	if (p == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (GenArgs2LibraryEntry **)Dz1Calloc(sizeof(GenArgs2LibraryEntry *), (cnt = p->count(p)) + 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		GenArgs2LibraryRefIndexMkArrArg arg = { ret, 0 };
		pthread_cleanup_push(Dz1Memory_cancel, (void *)ret);

		*errp = p->travel(p, _GenArgs2LibraryRefIndex_get_array, (void *)&arg);
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

static Dz1Error GenArgs2LibraryRefIndex_travelForward(GenArgs2LibraryRefIndex *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *data), void *ptr)
{
	return Dz1AATree_travelForward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static Dz1Error GenArgs2LibraryRefIndex_travelBackward(GenArgs2LibraryRefIndex *p, Dz1Error (*func)(void *ptr, GenArgs2LibraryEntry *data), void *ptr)
{
	return Dz1AATree_travelBackward(p->storage, (Dz1AATreeTravelFunc)func, ptr);
}

static GenArgs2LibraryEntry *GenArgs2LibraryRefIndex_find(GenArgs2LibraryRefIndex *p, GenArgs2LibraryEntry *key)
{
	return (GenArgs2LibraryEntry *)Dz1AATree_find(p->storage, key);
}

static GenArgs2LibraryEntry *GenArgs2LibraryRefIndex_getTail(GenArgs2LibraryRefIndex *p)
{
	return (GenArgs2LibraryEntry *)Dz1AATree_getTail(p->storage);
}

static unsigned int GenArgs2LibraryRefIndex_count(GenArgs2LibraryRefIndex *p)
{
	unsigned int ret = Dz1AATree_count(p->storage);
	return ret;
}

static int _GenArgs2LibraryRefIndex_cmp(GenArgs2LibraryEntry *a, GenArgs2LibraryEntry *b)
{
	int ret = 0;
	if (a == NULL && b == NULL) ret = 0;
	else if (a == NULL /* && b == NULL*/) ret = -1;
	else if (/*a == NULL &&*/ b == NULL) ret = 1;
	else if ((ret = Dz1u32_cmp(&a->order, &b->order)) != 0) { }
	return ret;
}

GenArgs2LibraryRefIndex *GenArgs2LibraryRefIndex_new(Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryRefIndex *ret = (GenArgs2LibraryRefIndex *)Dz1Calloc(sizeof(GenArgs2LibraryRefIndex), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2LibraryRefIndex_delAndSetNull, (void *)&ret);

		if ((ret->storage = Dz1AATree_new((Dz1CmpFunc)_GenArgs2LibraryRefIndex_cmp, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->count = GenArgs2LibraryRefIndex_count;
			ret->travel = GenArgs2LibraryRefIndex_travelForward;
			ret->travelForward = GenArgs2LibraryRefIndex_travelForward;
			ret->travelBackward = GenArgs2LibraryRefIndex_travelBackward;
			ret->get_array = GenArgs2LibraryRefIndex_get_array;
			ret->add = GenArgs2LibraryRefIndex_add;
			ret->remove = GenArgs2LibraryRefIndex_remove;
			ret->find = GenArgs2LibraryRefIndex_find;
			ret->extract = GenArgs2LibraryRefIndex_extract;
			ret->getTail = GenArgs2LibraryRefIndex_getTail;
			ret->cmp = _GenArgs2LibraryRefIndex_cmp;
			ERR_CLEAR(errp);
		}
				pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Error _GenArgs2LibraryRefIndex_clone(void *ptr, GenArgs2LibraryEntry *data)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	GenArgs2LibraryRefIndex *p = (GenArgs2LibraryRefIndex *)ptr;
	GenArgs2LibraryEntry *cloned = data; // ref
	err = Dz1AATree_insert(p->storage, cloned); // chk
	if (ERR_PROBE(&err)) ERR_OUT(&err);
	return err;
}

GenArgs2LibraryRefIndex *GenArgs2LibraryRefIndex_clone(GenArgs2LibraryRefIndex *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2LibraryRefIndex *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = GenArgs2LibraryRefIndex_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2LibraryRefIndex_delAndSetNull, (void *)&ret);

		*errp = Dz1AATree_travelForward(src->storage, (Dz1AATreeTravelFunc)_GenArgs2LibraryRefIndex_clone, (void *)ret);

		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryRefIndex_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void GenArgs2LibraryRefIndex_purge(GenArgs2LibraryRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_empty(p->storage);
}

void GenArgs2LibraryRefIndex_del(GenArgs2LibraryRefIndex *p)
{
	if (!p) return;
	if (p->storage) Dz1AATree_del(p->storage);
	Dz1Free(p);
}

static Dz1Error _GenArgs2LibraryRefIndex_dump(void *ptr, GenArgs2LibraryEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ListFDumpArg2 *arg = (Dz1ListFDumpArg2 *)ptr;
	int tab = *(int *)arg->tab;
	Dz1Thread_tprintf(tab, Dz1T("entry = ")); GenArgs2LibraryEntry_dump(p, tab);
	return err;
}

void GenArgs2LibraryRefIndex_dump(GenArgs2LibraryRefIndex *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1ListFDumpArg2 arg = { NULL, &tab };
		Dz1Thread_tprintf(tab, Dz1T("{\n")); tab++;
		p->travel(p, _GenArgs2LibraryRefIndex_dump, (void *)&arg);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GenArgs2LibraryRefIndex
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2LibraryInfo
bool_t GenArgs2LibraryInfo_copy(GenArgs2LibraryInfo *dst, GenArgs2LibraryInfo *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->table && (dst->table = GenArgs2LibraryList_clone(src->table, errp)) == NULL) ERR_OUT(errp);
	else if (src->inorder && (dst->inorder = GenArgs2LibraryRefIndex_clone(src->inorder, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->add = src->add;
		dst->remove = src->remove;
		dst->find = src->find;
		dst->extract = src->extract;
		dst->get_array = src->get_array;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GenArgs2LibraryInfo *GenArgs2LibraryInfo_clone(GenArgs2LibraryInfo *src, Dz1Error *err)
{
	GenArgs2LibraryInfo *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GenArgs2LibraryInfo *)Dz1Calloc(sizeof(GenArgs2LibraryInfo), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GenArgs2LibraryInfo_delAndSetNull, (void *)&dst);
		if (GenArgs2LibraryInfo_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2LibraryInfo_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GenArgs2LibraryInfo_purge(GenArgs2LibraryInfo *p)
{
	if (p == NULL) return;
	GenArgs2LibraryList_del(p->table);
	GenArgs2LibraryRefIndex_del(p->inorder);
}

void GenArgs2LibraryInfo_del(GenArgs2LibraryInfo *p)
{
	if (p == NULL) return;
	GenArgs2LibraryInfo_purge(p);
	Dz1Free(p);
}

void GenArgs2LibraryInfo_dump(GenArgs2LibraryInfo *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("table = ")); GenArgs2LibraryList_dump(p->table, tab); 
		Dz1Thread_tprintf(tab, Dz1T("inorder = ")); GenArgs2LibraryRefIndex_dump(p->inorder, tab); 
		Dz1Thread_tprintf(tab, Dz1T("add = %p\n"), p->add);
		Dz1Thread_tprintf(tab, Dz1T("remove = %p\n"), p->remove);
		Dz1Thread_tprintf(tab, Dz1T("find = %p\n"), p->find);
		Dz1Thread_tprintf(tab, Dz1T("extract = %p\n"), p->extract);
		Dz1Thread_tprintf(tab, Dz1T("get_array = %p\n"), p->get_array);
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GenArgs2LibraryInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2VisualStudio
GenArgs2VisualStudio *GenArgs2VisualStudio_new(Dz1Str pthread_root, 
											   u32_t gen_project, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2VisualStudio *__internal_ret = (GenArgs2VisualStudio *)Dz1Calloc(sizeof(GenArgs2VisualStudio), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudio_delAndSetNull, (void *)&__internal_ret);
		
		if (pthread_root && (__internal_ret->pthread_root = Dz1Str_clone(pthread_root, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->gen_project = gen_project;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudio_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

bool_t GenArgs2VisualStudio_copy(GenArgs2VisualStudio *dst, GenArgs2VisualStudio *src, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (dst == NULL || src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if (src->pthread_root && (dst->pthread_root = Dz1Str_clone(src->pthread_root, errp)) == NULL) ERR_OUT(errp);
	else
	{
		dst->gen_project = src->gen_project;
		ERR_CLEAR(errp);
	}
	return ERR_PROBE(errp) ? FALSE : TRUE;
}

GenArgs2VisualStudio *GenArgs2VisualStudio_clone(GenArgs2VisualStudio *src, Dz1Error *err)
{
	GenArgs2VisualStudio *dst = NULL;
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	if (src == NULL) { ERR_SET_OUT(errp, EINVAL); }
	else if ((dst = (GenArgs2VisualStudio *)Dz1Calloc(sizeof(GenArgs2VisualStudio), 1, errp)) == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudio_delAndSetNull, (void *)&dst);
		if (GenArgs2VisualStudio_copy(dst, src, errp) == FALSE) ERR_SET_OUT(errp, EINVAL);
		else ERR_CLEAR(errp);
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2VisualStudio_delAndSetNull, (void *)&dst);
	}
	return dst;
}

void GenArgs2VisualStudio_purge(GenArgs2VisualStudio *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->pthread_root);
}

void GenArgs2VisualStudio_del(GenArgs2VisualStudio *p)
{
	if (p == NULL) return;
	GenArgs2VisualStudio_purge(p);
	Dz1Free(p);
}

void GenArgs2VisualStudio_dump(GenArgs2VisualStudio *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		Dz1Thread_tprintf(tab, Dz1T("pthread_root = ")); Dz1Str_dump(p->pthread_root, tab); 
		Dz1Thread_tprintf(tab, Dz1T("gen_project = ")); Dz1u32_dump(&p->gen_project, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// GenArgs2VisualStudio
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenArgs2
GenArgs2 *GenArgs2_new(Dz1Str gen_parent_path, 
					   Dz1GenTarget gen_target_type, 
					   Dz1Str gen_target_name, 
					   bool_t gen_test_main, 
					   bool_t gen_makefile, 
					   GenArgs2VisualStudio *gen_studios, 
					   Dz1GenTextMode txt_mode, 
					   Dz1TaskGenEndian endian, 
					   GenArgs2Naming name_rule, 
					   Dz1Str codeconv_root, 
					   Dz1Str dimz_root, 
					   GenArgs2LibraryInfo *libraries, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenArgs2 *__internal_ret = (GenArgs2 *)Dz1Calloc(sizeof(GenArgs2), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&__internal_ret);
		
		if (gen_parent_path && (__internal_ret->gen_parent_path = Dz1Str_clone(gen_parent_path, errp)) == NULL) ERR_OUT(errp);
		else if (gen_target_name && (__internal_ret->gen_target_name = Dz1Str_clone(gen_target_name, errp)) == NULL) ERR_OUT(errp);
		else if (codeconv_root && (__internal_ret->codeconv_root = Dz1Str_clone(codeconv_root, errp)) == NULL) ERR_OUT(errp);
		else if (dimz_root && (__internal_ret->dimz_root = Dz1Str_clone(dimz_root, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->gen_target_type = gen_target_type;
			__internal_ret->gen_test_main = gen_test_main;
			__internal_ret->gen_makefile = gen_makefile;
			__internal_ret->gen_studios = gen_studios;
			__internal_ret->txt_mode = txt_mode;
			__internal_ret->endian = endian;
			__internal_ret->name_rule = name_rule;
			__internal_ret->libraries = libraries;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenArgs2_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GenArgs2_purge(GenArgs2 *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->gen_parent_path);
	Dz1Str_del(p->gen_target_name);
	GenArgs2VisualStudio_del(p->gen_studios);
	Dz1Str_del(p->codeconv_root);
	Dz1Str_del(p->dimz_root);
	GenArgs2LibraryInfo_del(p->libraries);
}

void GenArgs2_del(GenArgs2 *p)
{
	if (p == NULL) return;
	GenArgs2_purge(p);
	Dz1Free(p);
}

// GenArgs2
////////////////////////////////////////////////////////////////////////////////


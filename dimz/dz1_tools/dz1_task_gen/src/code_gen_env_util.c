#include "code_gen.h"
#include "code_gen_env_util.h"
#include "txt_replace_env_util.h"

///////////////////////////////////////////////////////////////////////////////
// dz1_text_file.h
typedef enum Dz1TextBom
{
	Dz1TextBom_ucs4,
	Dz1TextBom_ucs2le,
	Dz1TextBom_ucs2be,
	Dz1TextBom_utf8,
	Dz1TextBom_max
} Dz1TextBom;

#ifndef UNIX_SYSTEM
#ifdef UNICODE
#define Dz1TextFile_loadExt			Dz1TextFileW_loadExt
#else // UNICODE
#define Dz1TextFile_loadExt			Dz1TextFileA_loadExt
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1TextFile_loadExt			Dz1TextFileA_loadExt
#endif // UNIX_SYSTEM
// dz1_text_file.h
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// dz1_text_file.c
static str_t Dz1TextBomName[] =
{
	"UCS-4",
	"UCS-2LE",
	"UCS-2BE",
	"UTF-8",
	"Unknown"
};

static u8_t Dz1TextBomUCS4[]	= { 0xFF, 0xFF, 0xFF, 0xFF };
static u8_t Dz1TextBomUCS2LE[]	= { 0xFE, 0xFF };
static u8_t Dz1TextBomUCS2BE[]	= { 0xFF, 0xFE };
static u8_t Dz1TextBomUTF8[]	= { 0xEF, 0xBB, 0xBF };
Dz1Binary Dz1TextBomData[] =
{
	{ Dz1TextBomUCS4, 4 },
	{ Dz1TextBomUCS2LE, 2 },
	{ Dz1TextBomUCS2BE, 2 },
	{ Dz1TextBomUTF8, 3 },
	{ NULL, 0 }
};

static Dz1TextBom _find_bom(u8_t *data, size_t sz)
{
	Dz1Binary *i;
	Dz1TextBom ret = Dz1TextBom_ucs4;
	for (i = Dz1TextBomData; i->size != 0; i++, ret++)
		if (sz > i->size && memcmp(data, i->data, i->size) == 0) break;
	return ret;
}

str_t Dz1TextFileA_loadExt(str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	Dz1Binary *bin = Dz1BinFileA_load(fn, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		size_t ret_size = 0;
		Dz1TextBom bom = Dz1TextBom_max;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((bom = _find_bom(bin->data, bin->size)) != Dz1TextBom_max)
		{	// known text char-set, most letters are shrink(4->2, 3->2, 2->2)
			size_t unit_sz = 2;
			if ((ret = (str_t)Dz1Calloc(sizeof(char), (ret_size = ((bin->size + 1) * unit_sz)), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&ret);

				if ((sz = Dz1CodeConv((u8_t *)ret, ret_size, DZ1_SYSTEM_MBCS_CHARSET, bin->data, bin->size, Dz1TextBomName[bom])) < 0) ERR_SET_OUT(errp, EFAULT);
				else if (sz == 0) ERR_SET_OUT(errp, EINVAL);
				else Dz1Error_set(errp, 0);

				pthread_cleanup_pop(errp->code); // (Dz1StrA_delAndSetNull, (void *)&ret);
			}
		}
		else if ((ret = (str_t)Dz1Calloc(sizeof(char), (ret_size = bin->size + 1), errp)) == NULL) ERR_OUT(errp);
		else
		{	// force ansi
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&ret);

			if ((sz = Dz1CodeConv((u8_t *)ret, ret_size, DZ1_SYSTEM_MBCS_CHARSET, bin->data, bin->size, DZ1_SYSTEM_MBCS_CHARSET)) < 0) ERR_SET_OUT(errp, EFAULT);
			else if (sz == 0) ERR_SET_OUT(errp, EINVAL);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1StrA_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}
#ifndef UNIX_SYSTEM
wstr_t Dz1TextFileW_loadExt(wstr_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	Dz1Binary *bin = Dz1BinFileW_load(fn, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		size_t ret_size = 0, unit_sz = 2;
		Dz1TextBom bom = Dz1TextBom_max;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((bom = _find_bom(bin->data, bin->size)) != Dz1TextBom_max)
		{	// known text char-set : stretch or shrink(1->2, 4->2, 3->2)
			if ((ret = (wstr_t)Dz1Calloc(sizeof(u8_t), (ret_size = ((bin->size + 1) * unit_sz)), errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&ret);

				if ((sz = Dz1CodeConv((u8_t *)ret, ret_size, DZ1_SYSTEM_WIDE_CHARSET, bin->data, bin->size, Dz1TextBomName[bom])) < 0) ERR_SET_OUT(errp, EFAULT);
				else if (sz == 0) ERR_SET_OUT(errp, EINVAL);
				else Dz1Error_set(errp, 0);

				pthread_cleanup_pop(errp->code); // (Dz1StrW_delAndSetNull, (void *)&ret);
			}
		}
		else if ((ret = (wstr_t)Dz1Calloc(sizeof(u8_t), (ret_size = ((bin->size + 1) * unit_sz)), errp)) == NULL) ERR_OUT(errp);
		else
		{	// force ansi : 1->2, 2->2
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&ret);

			if ((sz = Dz1CodeConv((u8_t *)ret, ret_size, DZ1_SYSTEM_WIDE_CHARSET, bin->data, bin->size, DZ1_SYSTEM_MBCS_CHARSET)) < 0) ERR_SET_OUT(errp, EFAULT);
			else if (sz == 0) ERR_SET_OUT(errp, EINVAL);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (Dz1StrA_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ret;
}
#endif // UNIX_SYSTEM
// dz1_text_file.c
///////////////////////////////////////////////////////////////////////////////

GenArgs2VisualStudioEntry *GenArgs2VisualStudioList_getProj(GenArgs2VisualStudioList *list, GenArgs2VisualStudioVer ver)
{
	GenArgs2VisualStudioEntry *ret = NULL;
	if (list != NULL)
	{
		GenArgs2VisualStudioEntry key = { ver };
		ret = list->find(list, &key);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Visual Studio Project File Utility
typedef struct VisualStudioAPI
{
	GenArgs2VisualStudioVer		 ver;
	bool_t						 (*load_guid)(TCHAR dst[40], Dz1Str fn, Dz1Error *err);
} VisualStudioAPI;

static bool_t _load_guid_vc90(TCHAR dst[40], Dz1Str fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str text = Dz1TextFile_loadExt(fn, errp);
	if (text == NULL) ERR_OUT(errp);
	else
	{
		size_t sz = 40;
		TCHAR *cp = NULL, *dp = dst;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
		if ((cp = Dz1STRSTR(text, Dz1T("ProjectGUID") )) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			while (*cp != Dz1T('{')) cp++;
			while(sz && *cp != Dz1T('}')) { *dp++ = *cp++; sz--; }
			if (sz > 1) { *dp++ = Dz1T('}'); *dp = 0; } else ERR_SET_OUT(errp, E2BIG);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _load_guid_vs2022(TCHAR dst[40], Dz1Str fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1Str text = Dz1TextFile_loadExt(fn, errp);
	if (text == NULL) ERR_OUT(errp);
	else
	{
		size_t sz = 40;
		TCHAR *cp = NULL, *dp = dst;
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&text);
		if ((cp = Dz1STRSTR(text, Dz1T("<ProjectGuid>") )) == NULL) ERR_SET_OUT(errp, ENOENT);
		else
		{
			while (*cp != Dz1T('{')) cp++;
			while(sz && *cp != Dz1T('}')) { *dp++ = *cp++; sz--; }
			if (sz > 1) { *dp++ = Dz1T('}'); *dp = 0; } else ERR_SET_OUT(errp, E2BIG);
		}
		pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&text);
	}
	return errp->code == 0 ? TRUE : FALSE;
}


static VisualStudioAPI visualStudioAPI[] =
{
	{ GenArgs2VisualStudioVer_vc90,		_load_guid_vc90 },
	{ GenArgs2VisualStudioVer_vs2022,	_load_guid_vs2022 },
	{ GenArgs2VisualStudioVer_max,		NULL }
};

static VisualStudioAPI *VisualStudioAPI_find(GenArgs2VisualStudioVer ver)
{
	VisualStudioAPI *i;
	for (i = visualStudioAPI; i->ver != GenArgs2VisualStudioVer_max; i++)
		if (i->ver == ver) return i;
	return NULL;
}

bool_t _load_proj_guid(TCHAR dst[40], Dz1Str lib_root_abs, Dz1Str middle_path, Dz1Str proj_file_name, GenArgs2VisualStudioVer ver, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR fn[2048];
	VisualStudioAPI *api = NULL;
	if ((api = VisualStudioAPI_find(ver)) == NULL) ERR_SET_OUT(errp, ENOSYS);
	else if ((*errp = Dz1PathStr_concat(fn, 2048, lib_root_abs, middle_path, proj_file_name, NULL)).code) ERR_OUT(errp);
	else if (api->load_guid(dst, fn, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Visual Studio Project File Utility
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Project Loader
static LoadProjectMap loadProjectMap[] =
{
	{ GenArgs2VisualStudioVer_vc90,		Dz1T("vc90"),		Dz1T("vcproj") },
	{ GenArgs2VisualStudioVer_vs2022,	Dz1T("vs2022"),		Dz1T("vcxproj") },
	{ GenArgs2VisualStudioVer_max,		NULL,				NULL }
};

LoadProjectMap *LoadProjectMap_find(GenArgs2VisualStudioVer ver)
{
	LoadProjectMap *i = NULL;
	for (i = loadProjectMap; i->ver != GenArgs2VisualStudioVer_max; i++)
		if (i->ver == ver) return i;
	return NULL;
}

static bool_t _append_project(GenArgs2VisualStudioList *dst, LoadProjectMap *map, Dz1Str lib_root_abs, Dz1Str lib_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR middle_path[64];
	if ((*errp = Dz1PathStr_concat(middle_path, 64, Dz1T("project"), map->branch_path, NULL)).code) ERR_OUT(errp);
	else if (Dz1Dir_isExist2(lib_root_abs, middle_path) == TRUE)
	{
		GenArgs2VisualStudioEntry *node = NULL;
		// TCHAR proj_file_name[128] = { 0, }, proj_guid[40] = { 0, };
		TCHAR proj_file_name[4096] = { 0, }, proj_guid[40] = { 0, }; // modified by gm 20230602 - size of name 128->4096
		if (_Dz1FileName_concatNameExt(Dz1ArrParam(TCHAR, proj_file_name), lib_name, map->proj_ext, errp) == FALSE) ERR_OUT(errp);							// {lib_name}.{vcproj}
		else if (_load_proj_guid(proj_guid, lib_root_abs, middle_path, proj_file_name, map->ver, errp) == FALSE) ERR_OUT(errp);
		else if ((node = GenArgs2VisualStudioEntry_new(map->ver, middle_path, proj_file_name, proj_guid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
			if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
			else
			{
				node = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _append_library_project(GenArgs2VisualStudioList *dst, Dz1Str lib_root_abs, Dz1Str lib_name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	LoadProjectMap *i;
	for (i = loadProjectMap; i->ver != GenArgs2VisualStudioVer_max; i++)
	{
		if (_append_project(dst, i, lib_root_abs, lib_name, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Project Loader
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Replacer generate
static bool_t _reg_endian_replate(TxtReplaceEnv *dst, Dz1TaskGenEndian ed, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	switch(ed)
	{
	case Dz1TaskGenEndian_Little:
		if ((*errp = TxtReplaceEnv_addReplace(dst, Dz1T("SYSTEM_ENDIAN_DEF"), Dz1T("__SYSTEM_ENDIAN_LITTLE__") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case Dz1TaskGenEndian_Big:
		if ((*errp = TxtReplaceEnv_addReplace(dst, Dz1T("SYSTEM_ENDIAN_DEF"), Dz1T("__SYSTEM_ENDIAN_BIG__") )).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	default:
		ERR_SET_OUT(errp, EINVAL);
		break;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t __append_include(Dz1ElasticBuf *dst, Dz1Str proj_root_abs, Dz1Str _toPath, Dz1Str _toOptPath, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	TCHAR relative_path[2048] = { 0, }, fromPath[2048] = { 0, }, toPath[2048] = { 0, };
	if (0) { }
	else if ((*errp = Dz1PathStr_concat(fromPath, 2048, proj_root_abs, Dz1T("project"), Dz1T("vs_ver"), NULL)).code) ERR_OUT(errp);
	else if ((*errp = Dz1PathStr_concat(toPath, 2048, _toPath, _toOptPath, NULL)).code) ERR_OUT(errp);
	else if (_get_relative_path(relative_path, 2048, fromPath, toPath, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1ElasticBuf_getDataSize(dst, NULL) > 0 && Dz1ElasticBuf_pushChr(dst, Dz1T(';'), errp) == FALSE) ERR_OUT(errp);
	else if (Dz1ElasticBuf_pushStr(dst, relative_path, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

typedef struct RegTargetIncludesArg
{
	Dz1Str					 proj_root_abs;
	Dz1ElasticBuf			*dst_elb;
} RegTargetIncludesArg;

static Dz1Error _append_includes(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	RegTargetIncludesArg *arg = (RegTargetIncludesArg *)ptr;
	if (__append_include(arg->dst_elb, arg->proj_root_abs, p->path_root_abs, p->root2inc_path, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static bool_t _reg_target_includes(TxtReplaceEnv *rp_env, Dz1Str rp_name, 
								   Dz1Str proj_root_abs, Dz1Str dimz_root, Dz1Str codeconv_root,
								   GenArgs2LibraryRefIndex *libs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1ElasticBuf *dst_elb = NULL;
	
	if ((dst_elb = Dz1ElasticBuf_new(1024, FALSE, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Str text = NULL;
		RegTargetIncludesArg arg = { proj_root_abs, dst_elb };
		pthread_cleanup_push(Dz1ElasticBuf_delAndSetNull, (void *)&dst_elb);

		if (Dz1ElasticBuf_pushStr(dst_elb, Dz1T("..\\..\\include"), errp) == FALSE) ERR_OUT(errp);							// ..\..\include
		else if ((*errp = libs->travel(libs, _append_includes, (void *)&arg)).code) ERR_OUT(errp);							// each libraries include
		else if (__append_include(dst_elb, proj_root_abs, dimz_root, Dz1T("dz1\\include"), errp) == FALSE) ERR_OUT(errp);	// ...\dimz\dz1\include
		else if (__append_include(dst_elb, proj_root_abs, codeconv_root, Dz1T("include"), errp) == FALSE) ERR_OUT(errp);	// ...\codeconv\include
		else if ((text = Dz1ElasticBuf_flattenStr(dst_elb, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(rp_env, rp_name, text)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1ElasticBuf_delAndSetNull, (void *)&dst_elb);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _reg_named_relative_path(TxtReplaceEnv *rp_env, Dz1Str rp_name, Dz1Str proj_root_abs, Dz1Str _toPath, Dz1Str _toOptPath, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR relative_path[2048] = { 0, }, fromPath[2048] = { 0, }, toPath[2048] = { 0, };
	if (0) { }
	else if ((*errp = Dz1PathStr_concat(fromPath, 2048, proj_root_abs, Dz1T("project"), Dz1T("vs_ver"), NULL)).code) ERR_OUT(errp);
	else if ((*errp = Dz1PathStr_concat(toPath, 2048, _toPath, _toOptPath, NULL)).code) ERR_OUT(errp);
	else if (_get_relative_path(relative_path, 2048, fromPath, toPath, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = TxtReplaceEnv_addReplace(rp_env, rp_name, relative_path)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static TxtReplaceEnv *TxtReplaceEnv_generate(GenArgs2 *config, GenEnvVisualStudio *vs_env, Dz1Str proj_root_abs, Dz1Error *err)
{	// proj_name = "foo_bar", rule = GenArgs2Naming_underscore
	DZ1_ERROR_SAFE_PTR(errp, err);
	TxtReplaceEnv *ret = NULL;

	Dz1Str proj_name = config->gen_target_name;
	GenArgs2Naming		 rule		= config->name_rule;
	GenArgs2LibraryInfo *lib_config = config->libraries;

	if ((ret = TxtReplaceEnv_new(Dz1T("[["), Dz1Text("]]"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		TCHAR temp[2048] = { 0, };
		pthread_cleanup_push(TxtReplaceEnv_delAndSetNull, (void *)&ret);

		if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_NAME"), proj_name)).code) ERR_OUT(errp);

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("test"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TEST_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_test

		else if (_getStructureName(temp, 2048, proj_name, NULL, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_STRUCT_NAME"), temp)).code) ERR_OUT(errp);	// FooBar

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("def"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TDC_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_def

		else if (_getDefineName(temp, 2048, proj_name, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_HDR_DEFINE"), temp)).code) ERR_OUT(errp);	// FOO_BAR
		
		else if (_getStructureName(temp, 2048, proj_name, Dz1T("arg"), errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("STRUCT_ARG_NAME"), temp)).code) ERR_OUT(errp);	// FooBarArg

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("arg"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_ARG_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_arg

		else if (_getStructureName(temp, 2048, proj_name, Dz1T("env"), errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("STRUCT_ENV_NAME"), temp)).code) ERR_OUT(errp);	// FooBarEnv

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("env"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_ENV_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_env

		else if (_getStructureName(temp, 2048, proj_name, Dz1T("timer"), errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("STRUCT_TMR_NAME"), temp)).code) ERR_OUT(errp);	// FooBarTimer

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("timer"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TMR_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_timer

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("timer_util"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TMR_UTIL_NAME"), temp)).code) ERR_OUT(errp);	// foo_bar_timer_util

		else if (_getStructureName(temp, 2048, proj_name, Dz1T("msg"), errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("STRUCT_MSG_NAME"), temp)).code) ERR_OUT(errp);	// FooBarMsg

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("msg"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_MSG_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_msg

		else if (_getRuledName(temp, 2048, proj_name, Dz1T("msgs"), rule, errp) == FALSE) ERR_OUT(errp);
		else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_MSGS_NAME"), temp)).code) ERR_OUT(errp);		// foo_bar_msgs

		else if (_reg_endian_replate(ret, config->endian, errp) == FALSE) ERR_OUT(errp);						// SYSTEM_ENDIAN_DEF	__SYSTEM_ENDIAN_LITTLE__

		else if (_reg_target_includes(ret, Dz1T("PROJ_INCLUDES"), proj_root_abs, config->dimz_root, config->codeconv_root,
									  lib_config->inorder, errp) == FALSE) ERR_OUT(errp);	// 	PROJ_INCLUDES		path#1;path#2;...path#n

		else if (_reg_named_relative_path(ret, Dz1T("DIMZ_TOOLS_PATH"), proj_root_abs, 
										  config->dimz_root, Dz1T("dz1_tools"), errp) == FALSE) ERR_OUT(errp);	// 	DIMZ_TOOLS_PATH                 ..\..\..\dimz\dz1_tools
		else if (vs_env != NULL)
		{
			GenArgs2VisualStudio *vs_config = config->gen_studios;
			if (0) { }
			else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TARGET_GUID"),vs_env->target_guid)).code) ERR_OUT(errp);	// PROJ_TARGET_GUID		{.....} : GUID of Target Project
			else if ((*errp = TxtReplaceEnv_addReplace(ret, Dz1T("PROJ_TEST_GUID"), vs_env->test_guid)).code) ERR_OUT(errp);	// PROJ_TEST_GUID		{.....} : GUID of Test Project
			else if (_reg_named_relative_path(ret, Dz1T("PTHREAD_ROOT"), proj_root_abs,
														  vs_config->pthread_root, NULL, errp) == FALSE) ERR_OUT(errp);			//	PTHREAD_ROOT                    ..\..\..\pthreads.2
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (TxtReplaceEnv_delAndSetNull, (void *)&ret);
	}

	return ret;
}
// Replacer generate
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// GenEnv generate
static bool_t _generate_library_entry_projects(GenArgs2LibraryEntry *dst, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
//	TCHAR lib_proj_path_abs[2048];
	if (0) { }
//	else if (Dz1Dir_isExist2(dst->path_root_abs, Dz1T("project") ) == FALSE) ERR_SET_OUT(errp, ENOENT);
//	else if ((*errp = Dz1PathStr_concat(lib_proj_path_abs, 2048, dst->path_root_abs, Dz1T("project"), NULL)).code) ERR_OUT(errp);
	else if (_append_library_project(dst->projects, dst->path_root_abs, dst->name, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static GenArgs2LibraryEntry *_generate_library_entry(Dz1Str lib_root_abs, Dz1Str lib_name, u32_t order, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2LibraryEntry *ret = NULL;
	
	if ((ret = GenArgs2LibraryEntry_new(lib_name, lib_root_abs, order, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2LibraryEntry_delAndSetNull, (void *)&ret);
		if (0) { }
		else if (Dz1Dir_isExist2(lib_root_abs, Dz1T("include") ) == FALSE) ERR_SET_OUT(errp, ENOENT);
		else if ((ret->root2inc_path = Dz1Str_dup(Dz1T("include"), errp)) == NULL) ERR_OUT(errp);

		else if (Dz1Dir_isExist2(lib_root_abs, Dz1T("lib") ) == FALSE) ERR_SET_OUT(errp, ENOENT);
		else if ((ret->root2lib_path = Dz1Str_dup(Dz1T("lib"), errp)) == NULL) ERR_OUT(errp);

		else if (_generate_library_entry_projects(ret, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (GenArgs2LibraryEntry_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static bool_t _append_vc_project(GenArgs2VisualStudioList *dst, GenArgs2VisualStudioVer ver, Dz1Str proj_name, Dz1Str proj_guid, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR vc_proj_name_ext[4096], middle_path[64];
	GenArgs2VisualStudioEntry *node = NULL;
	LoadProjectMap *map = LoadProjectMap_find(ver);
	if (map == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (_Dz1FileName_concatNameExt(Dz1ArrParam(TCHAR, vc_proj_name_ext), proj_name, map->proj_ext, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = Dz1PathStr_concat(middle_path, 64, Dz1T("project"), map->branch_path, NULL)).code) ERR_OUT(errp);
	else if ((node = GenArgs2VisualStudioEntry_new(ver, middle_path, vc_proj_name_ext, proj_guid, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
		if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
		else
		{
			node = NULL;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (GenArgs2VisualStudioEntry_delAndSetNull, (void *)&node);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_vc_project(GenArgs2VisualStudioList *dst, Dz1Str proj_name, Dz1Str proj_guid, u32_t gen_flags, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (0) { }
	else if ((gen_flags & CODE_GEN_FLAG_VC90) && _append_vc_project(dst, GenArgs2VisualStudioVer_vc90, proj_name, proj_guid, errp) == FALSE) ERR_OUT(errp);
	else if ((gen_flags & CODE_GEN_FLAG_VS2022) && _append_vc_project(dst, GenArgs2VisualStudioVer_vs2022, proj_name, proj_guid, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _init_vs_env_test(GenEnvVisualStudio *dst, GenArgs2 *config, Dz1Str target_path_abs, u32_t gen_flags, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((dst->test_guid = GetGUIDStr(errp)) == NULL) ERR_OUT(errp);
	else 
	{
		pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&dst->test_guid);
		if (config->gen_test_main)
		{
			GenArgs2LibraryEntry *temp = NULL;
			TCHAR test_name[1024];
			if (_getRuledName(test_name, 1024, config->gen_target_name, Dz1T("test"), config->name_rule, errp) == FALSE) ERR_OUT(errp);
			else if ((dst->test = temp = GenArgs2LibraryEntry_new(test_name, target_path_abs, 0, Dz1T("include"), Dz1T("lib"), errp)) == NULL) ERR_OUT(errp);
			else if (_init_vc_project(temp->projects, test_name, dst->test_guid, gen_flags, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Str_delAndSetNull, (void *)&dst->test_guid);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t GenEnv_generate_vs(GenEnv *dst, GenArgs2 *config, Dz1Str target_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	// GenEnvVisualStudio *vs_env = NULL; // modified by gm 20230602 - unused var vs_env
	GenArgs2VisualStudio *vs_cfg = config->gen_studios;

	if (vs_cfg != NULL)
	{
		GenArgs2LibraryEntry *temp = NULL;
		GenEnvVisualStudio *vs_env = NULL;
		if (dst->vs_env != NULL) ERR_SET_OUT(errp, EFAULT);
		else if (vs_cfg->gen_project == 0 || Dz1Str_isVoid(vs_cfg->pthread_root)) ERR_SET_OUT(errp, EINVAL);
		else if ((dst->vs_env = vs_env = GenEnvVisualStudio_new(NULL, NULL, NULL, NULL, NULL, errp)) == NULL) ERR_SET_OUT(errp, EFAULT);
		else
		{
			pthread_cleanup_push(GenEnvVisualStudio_delAndSetNull, (void *)&dst->vs_env);

			dst->gen_flags |= CODE_GEN_FLAG_VISUAL_STUDIO;
			if (vs_cfg->gen_project & DZ1_TASK_GEN_SOLUTION)	dst->gen_flags |= CODE_GEN_FLAG_SOLUTION;
			if (vs_cfg->gen_project & DZ1_TASK_GEN_VC90)		dst->gen_flags |= CODE_GEN_FLAG_VC90;
			if (vs_cfg->gen_project & DZ1_TASK_GEN_VS2022)		dst->gen_flags |= CODE_GEN_FLAG_VS2022;

			if ((vs_env->target_guid = GetGUIDStr(errp)) == NULL) ERR_OUT(errp);
			else if ((vs_env->target = temp = GenArgs2LibraryEntry_new(config->gen_target_name, target_path_abs, 0, 
																	   Dz1T("include"), Dz1T("lib"), errp)) == NULL) ERR_OUT(errp);				// target(0)
			else if (_init_vc_project(temp->projects, temp->name, vs_env->target_guid, dst->gen_flags, errp) == FALSE) ERR_OUT(errp);

			else if (_init_vs_env_test(vs_env, config, target_path_abs, dst->gen_flags, errp) == FALSE) ERR_OUT(errp);
			else if ((vs_env->ptw_win = GenArgs2LibraryEntry_new(Dz1T("pthread"), vs_cfg->pthread_root, 0xFFFFFFFF, 
																 NULL, Dz1T("lib"), errp)) == NULL) ERR_OUT(errp);								// ptw_win(0xFFFFFFFF)
			else if (_generate_library_entry_projects(vs_env->ptw_win, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(errp->code); // (GenEnvVisualStudio_delAndSetNull, (void *)&dst->vs_env);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _initialize_library_test(GenEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	GenEnvVisualStudio *vs_env = NULL;
	GenArgs2LibraryRefIndex *libs_test = env->libs_test;
	if (0) { }
	else if ((*errp = libs_test->add(libs_test, env->codeconv)).code) ERR_OUT(errp);
	else if ((*errp = libs_test->add(libs_test, env->dimz_dz1)).code) ERR_OUT(errp);
	else if ((vs_env = env->vs_env) != NULL)
	{
		if ((*errp = libs_test->add(libs_test, vs_env->target)).code) ERR_OUT(errp);
		else if ((*errp = libs_test->add(libs_test, vs_env->ptw_win)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

GenEnv *GenEnv_generate(GenArgs2 *config, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnv *ret = NULL;
	TCHAR target_path_abs[2048] = { 0, };
	TCHAR dz1_path_abs[2048] = { 0, };
	GenArgs2LibraryInfo *libs = config->libraries;

	if (Dz1Str_isVoid(config->gen_parent_path) || Dz1Str_isVoid(config->gen_target_name)) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(config->codeconv_root) || Dz1Str_isVoid(config->dimz_root)) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1PathStr_concat(target_path_abs, 2048, config->gen_parent_path, config->gen_target_name, NULL)).code) ERR_OUT(errp);
	else if ((*errp = Dz1PathStr_concat(dz1_path_abs, 2048, config->dimz_root, Dz1T("dz1"), NULL)).code) ERR_OUT(errp);
	else if ((ret = GenEnv_new(NULL, 0, config->name_rule, config->txt_mode, NULL, NULL, libs->inorder, NULL, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		// GenEnvVisualStudio *vs_env = NULL; // modified by gm 20230602 - unused var vs_env
		pthread_cleanup_push(GenEnv_delAndSetNull, (void *)&ret);

		switch(config->gen_target_type)
		{
		default:
		case Dz1GenTarget_StaticLibrary:
			ret->gen_flags |= CODE_GEN_FLAG_LIB;
			break;
		case Dz1GenTarget_Task:
			ret->gen_flags |= CODE_GEN_FLAG_TASK;
			break;
		}
		if (config->gen_test_main)	ret->gen_flags |= CODE_GEN_FLAG_TEST;
		if (config->gen_makefile)	ret->gen_flags |= CODE_GEN_FLAG_MAKEFILE;

		if ((ret->target_path_abs = Dz1Str_dup(target_path_abs, errp)) == NULL) ERR_OUT(errp);											// target_path_abs
		else if ((ret->dimz_dz1 = _generate_library_entry(dz1_path_abs, Dz1T("dz1"), 1, errp)) == NULL) ERR_OUT(errp);					// dimz_dz1(1)
		else if ((ret->codeconv = _generate_library_entry(config->codeconv_root, Dz1T("codeconv"), 2, errp)) == NULL) ERR_OUT(errp);	// codeconv(2)
		else if (GenEnv_generate_vs(ret, config, target_path_abs, errp) == FALSE) ERR_OUT(errp);										// vs_env
		else if (_initialize_library_test(ret, errp) == FALSE) ERR_OUT(errp);
		else if ((ret->rp_env = TxtReplaceEnv_generate(config, ret->vs_env, target_path_abs, errp)) == NULL) ERR_OUT(errp);				// rp_env
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (GenEnv_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// GenEnv generate
///////////////////////////////////////////////////////////////////////////////

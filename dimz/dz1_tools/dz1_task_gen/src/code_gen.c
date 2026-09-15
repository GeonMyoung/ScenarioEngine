#include "code_gen.h"
#include "code_gen_env_util.h"
#include "code_template.h"
#include "txt_replace_env_util.h"

typedef struct CodeGenFileNode
{
	Dz1Str						 ext;
	Dz1Str						 suffix_name;
	Dz1Str						*template;
	bool_t						 (*emit_func)(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);
	u32_t						 excute_flag;
} CodeGenFileNode;

typedef struct CodeGenTreeNode
{
	Dz1Str						 work_path;
	CodeGenFileNode				*files;
	struct CodeGenTreeNode		**childs;
	u32_t						 excute_flag;
} CodeGenTreeNode;

///////////////////////////////////////////////////////////////////////////////
// include
static CodeGenFileNode _include_files[] =
{
	{ Dz1T("tdc"),	Dz1T("def"),			task_def2,			NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("h"),	Dz1T(""),				task_main_hdr2,		NULL, CODE_GEN_FLAG_TASK },

	{ Dz1T("tdc"),	Dz1T("def"),			lib_def2,			NULL, CODE_GEN_FLAG_LIB },
	{ Dz1T("h"),	Dz1T(""),				lib_main_hdr2,		NULL, CODE_GEN_FLAG_LIB },

	{ NULL,			NULL,					NULL,				NULL, CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _include_node_ =
{
	Dz1T("include"),
	_include_files,
	NULL,
	0
};
// include
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// src
static CodeGenFileNode _src_files[] =
{
	{ Dz1T("tdc"),	Dz1T("arg"),			task_arg_def2,			NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("tdc"),	Dz1T("env"),			task_env_def2,			NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("tdc"),	Dz1T("timer"),			task_timer_def2,		NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("h"),	Dz1T("timer_util"),		task_timer_util_hdr2,	NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("c"),	Dz1T("timer_util"),		task_timer_util_src2,	NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("h"),	Dz1T("msg"),			task_msg_hdr2,			NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("tdc"),	Dz1T("msgs"),			task_msgs_def2,			NULL, CODE_GEN_FLAG_TASK },
	{ Dz1T("c"),	Dz1T(""),				task_main_src2,			NULL, CODE_GEN_FLAG_TASK },
//	{ Dz1T(""),		Dz1T(""),				task_makefile,			NULL, CODE_GEN_FLAG_TASK_MAKEFILE },

	{ Dz1T("c"),	Dz1T(""),				lib_main_src2,			NULL, CODE_GEN_FLAG_LIB },
//	{ Dz1T(""),		Dz1T(""),				lib_makefile,			NULL, CODE_GEN_FLAG_LIB_MAKEFILE },
	{ NULL,			NULL,					NULL,					NULL, CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _src_node_ =
{
	Dz1T("src"),
	_src_files,
	NULL,
	0
};
// src
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// {project_name}.txt
static Dz1Str common_lib_txt[] =
{
Dz1T("don't delete me"),
NULL
};
// {project_name}.txt
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// lib
static CodeGenFileNode _lib_files[] =
{
	{ Dz1T("txt"),	Dz1T(""),				common_lib_txt,			NULL, 0 },
	{ NULL,			NULL,					NULL,					NULL, CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _lib_node_ =
{
	Dz1T("lib"),
	_lib_files,
	NULL,
	0
};
// lib
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// vc90
static CodeGenFileNode _vc90_files[] =
{
	{ Dz1T("vcproj"),			Dz1T(""),		vc90_library_proj,		NULL,					CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VC90 | CODE_GEN_FLAG_LIB },
	{ Dz1T("vcproj"),			Dz1T(""),		vc90_task_proj,			NULL,					CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VC90 | CODE_GEN_FLAG_TASK },
	{ Dz1T("vcproj"),			Dz1T("test"),	vc90_test_proj,			NULL,					CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VC90 | CODE_GEN_FLAG_TEST },
	{ Dz1T("sln"),				Dz1T(""),		NULL,					vc90_solution,			CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VC90 | CODE_GEN_FLAG_SOLUTION },
	{ NULL,						NULL,			NULL,					NULL,					CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _proj_node_childs_vc90 =
{
	Dz1T("vc90"),
	_vc90_files,
	NULL,
	CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VC90
};
// vc90
///////////////////////////////////////////////////////////////////////////////

#define SUPPORT_VS2022
#ifdef SUPPORT_VS2022
///////////////////////////////////////////////////////////////////////////////
// vs2022
static CodeGenFileNode _vs2022_files[] =
{
	{ Dz1T("vcxproj"),			Dz1T(""),		NULL,					_vs2022_lib_proj,		CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_LIB },
	{ Dz1T("vcxproj.filters"),	Dz1T(""),		NULL,					_vs2022_lib_filters,	CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_LIB },
	{ Dz1T("vcxproj"),			Dz1T(""),		NULL,					_vs2022_task_proj,		CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_TASK },
	{ Dz1T("vcxproj.filters"),	Dz1T(""),		NULL,					_vs2022_task_filters,	CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_TASK },
	{ Dz1T("vcxproj"),			Dz1T("test"),	NULL,					_vs2022_test_proj,		CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_TEST },
	{ Dz1T("vcxproj.filters"),	Dz1T("test"),	NULL,					_vs2022_test_filters,	CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_TEST },
	{ Dz1T("sln"),				Dz1T(""),		NULL,					_vs2022_sln,			CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022 | CODE_GEN_FLAG_SOLUTION },
	{ NULL,						NULL,			NULL,					NULL,					CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _proj_node_childs_vs2022=
{
	Dz1T("vs2022"),
	_vs2022_files,
	NULL,
	CODE_GEN_FLAG_VISUAL_STUDIO | CODE_GEN_FLAG_VS2022
};
// vs2022
///////////////////////////////////////////////////////////////////////////////
#endif

static CodeGenTreeNode *_proj_node_childs[] =
{
	&_proj_node_childs_vc90,
#ifdef SUPPORT_VS2022
	&_proj_node_childs_vs2022,
#endif
	NULL
};

static CodeGenTreeNode _prj_node_ =
{
	Dz1T("project"),
	NULL,
	_proj_node_childs,
	CODE_GEN_FLAG_VISUAL_STUDIO
};
///////////////////////////////////////////////////////////////////////////////
// {project_root}
static CodeGenTreeNode *_root_childs[] =
{
	&_include_node_,
	&_src_node_,
	&_lib_node_,
	&_prj_node_,
	NULL
};

static CodeGenFileNode _root_test_files[] =
{
// 	{ Dz1T("mk"),	Dz1T(""),				task_build,				NULL, CODE_GEN_FLAG_TASK | CODE_GEN_FLAG_MAKEFILE },
//	{ Dz1T(""),		Dz1T(""),				task_makefile,			NULL, CODE_GEN_FLAG_TASK | CODE_GEN_FLAG_MAKEFILE },
	{ Dz1T("c"),	Dz1T("test"),			task_test_src2,			NULL, CODE_GEN_FLAG_TASK | CODE_GEN_FLAG_TEST },

// 	{ Dz1T("mk"),	Dz1T(""),				lib_build,				NULL, CODE_GEN_FLAG_LIB | CODE_GEN_FLAG_MAKEFILE },
//	{ Dz1T(""),		Dz1T(""),				lib_makefile,			NULL, CODE_GEN_FLAG_LIB | CODE_GEN_FLAG_MAKEFILE },
	{ Dz1T("c"),	Dz1T("test"),			lib_test_src2,			NULL, CODE_GEN_FLAG_LIB | CODE_GEN_FLAG_TEST },
	{ NULL,			NULL,					NULL,					NULL, CODE_GEN_FLAG_MAX }
};

static CodeGenTreeNode _root_node =
{
	NULL,
	_root_test_files,
	_root_childs,
	0
};
// {project_root}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File generation
static bool_t _path_prepare(TCHAR *dst, size_t dst_size, Dz1Str abs_path, Dz1Str child_path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (dst == NULL || Dz1Str_isVoid(abs_path) || Dz1Str_isVoid(child_path)) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1PathStr_concat(dst, dst_size, abs_path, child_path, NULL)).code) ERR_OUT(errp);
	else if ((*errp = Dz1Dir_mkDirNested(dst)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generate_file(CodeGenFileNode *f, GenEnv *env, Dz1Str abs_path, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TxtReplaceEntry *proj_name = NULL;
	TCHAR fn[512] = { 0, };
	FILE *fp = NULL;
	if (f == NULL || Dz1Str_isVoid(abs_path)) ERR_SET_OUT(errp, EINVAL);
	else if ((proj_name = TxtReplaceEnv_find(env->rp_env, Dz1T("PROJ_NAME") )) == NULL) ERR_SET_OUT(errp, ENOENT);
	else if (_getRuledName(fn, 512, proj_name->replace, f->suffix_name, env->rule, errp) == FALSE) ERR_OUT(errp);
	else if ((fp = Dz1FileStream_open3(abs_path, fn, f->ext, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (f->emit_func != NULL)
		{
			if (f->emit_func(fp, env, abs_path, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
		else if (TxtReplaceEnv_do(env->rp_env, fp, f->template, env->txt_mode, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _generate_files(Dz1Str abs_path, CodeGenFileNode *files, GenEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1Str_isVoid(abs_path) || files == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		CodeGenFileNode *i;
		for (i = files; i->excute_flag != CODE_GEN_FLAG_MAX; i++)
		{
			if (i->excute_flag != 0 && (i->excute_flag & env->gen_flags) != i->excute_flag) continue;
			else if (_generate_file(i, env, abs_path, errp) == FALSE) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// File generation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Node Generation
static bool_t _CodeGenTree_execute(CodeGenTreeNode *node, Dz1Str abs_path, GenEnv *env, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TCHAR work_path[4096] = { 0, };
	if (node == NULL || Dz1Str_isVoid(abs_path) || env == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (node->excute_flag == 0 || (env->gen_flags & node->excute_flag) == node->excute_flag)
	{
		if (Dz1Str_isVoid(node->work_path) == FALSE && _path_prepare(work_path, 4096, abs_path, node->work_path, errp) == FALSE) ERR_OUT(errp);
		else if (node->files != NULL && _generate_files(work_path, node->files, env, errp) == FALSE) ERR_OUT(errp);
		else if (node->childs != NULL)
		{
			CodeGenTreeNode **i;
			for (i = node->childs; errp->code == 0 && *i != NULL; i++)
			{
				if (_CodeGenTree_execute(*i, work_path, env, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// Node Generation
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ReadMe.txt generation
static bool_t _generate_readme_txt(Dz1Str parent_path_abs, Dz1Str target_name, Dz1GenTextMode mode, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	TCHAR path[2048] = { 0, };
	if ((*errp = Dz1PathStr_concat(path, 2048, parent_path_abs, target_name, NULL)).code) ERR_OUT(errp);
	else if ((fp = Dz1FileStream_open2(path, Dz1T("ReadMe.txt"), Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		Dz1Thread_fprintf(fp, Dz1T("this is readme file")); _lf(fp, mode);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// ReadMe.txt generation
///////////////////////////////////////////////////////////////////////////////

bool_t Dz1TaskGen2_code_generate(GenArgs2 *config, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnv *g_env = GenEnv_generate(config, errp);
	if (g_env == NULL) ERR_OUT(errp);
	else
	{
		// TxtReplaceEnv *rp_env = g_env->rp_env; // modified by gm 20230602 - unused value rp_env
		pthread_cleanup_push(GenEnv_delAndSetNull, (void *)&g_env);

		_root_node.work_path = config->gen_target_name;
		if (_CodeGenTree_execute(&_root_node, config->gen_parent_path, g_env, errp) == FALSE) ERR_OUT(errp);
		else if (_generate_readme_txt(config->gen_parent_path, config->gen_target_name, config->txt_mode, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		_root_node.work_path = NULL;

		pthread_cleanup_pop(1); // (GenEnv_delAndSetNull, (void *)&g_env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}


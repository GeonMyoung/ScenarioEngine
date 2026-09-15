#include <dz1_task_gen.h>
#include "code_gen_env_util.h"
#include "code_template.h"

static ssize_t _sol_ftprintfA(FILE *fp, int tab, char *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;

	while(tab--) fprintf(fp, "\t");

	va_start(ap, fmt);
	vfprintf(fp, fmt, ap);
	va_end(ap);

	return ret;
}
#ifndef UNIX_SYSTEM
static ssize_t _sol_ftprintfW(FILE *fp, int tab, wchar_t *fmt, ...)
{
	ssize_t ret = -1;

	va_list ap;

	while(tab--) fwprintf(fp, L"\t");

	va_start(ap, fmt);
	vfwprintf(fp, fmt, ap);
	va_end(ap);

	return ret;
}
#ifdef UNICODE
#define _sol_ftprintf			_sol_ftprintfW
#else // UNICODE
#define _sol_ftprintf			_sol_ftprintfA
#endif // UNICODE
#else // UNIX_SYSTEM
#define _sol_ftprintf			_sol_ftprintfA
#endif // UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// emit Project dependency
static Dz1Error _vc90_solution_proj_dep(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	FILE *fp = (FILE *)arg->dst;
	GenArgs2VisualStudioEntry *project = GenArgs2VisualStudioList_getProj(p->projects, GenArgs2VisualStudioVer_vc90);
	if (project == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		_sol_ftprintf(fp, arg->tab, "%s = %s", project->proj_guid, project->proj_guid); _crlf(fp);
		Dz1Error_set(errp, 0);
	}
	return err;
}

static bool_t vc90_solution_proj_dep(FILE *fp, GenArgs2LibraryRefIndex *list, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TextEmitArg arg = { fp, NULL, tab };
	if ((*errp = list->travel(list, _vc90_solution_proj_dep, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
// emit Project dependency
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// emit Project
static bool_t vc90_solution_proj(FILE *fp, GenArgs2LibraryEntry *lib, Dz1Str sln_path_abs, GenArgs2LibraryRefIndex *inorder, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2VisualStudioList *projects = lib->projects;
	GenArgs2VisualStudioEntry *project = GenArgs2VisualStudioList_getProj(projects, GenArgs2VisualStudioVer_vc90);
	if (project == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		TCHAR this_vcproj_path_abs[1024] = { 0, }, relative_path[1024] = { 0, };
		TCHAR vc_proj_pathname[4096] = { 0, };
		if ((*errp = Dz1PathStr_concat(this_vcproj_path_abs, 1024, lib->path_root_abs, Dz1T("project"), project->middle_path, NULL)).code) ERR_OUT(errp);
		else if (_get_relative_path(relative_path, 2048, sln_path_abs, this_vcproj_path_abs, errp) == FALSE) ERR_OUT(errp);
		else if (_Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, vc_proj_pathname), relative_path, project->proj_file_name, errp) == FALSE) ERR_OUT(errp);
		else
		{
			_sol_ftprintf(fp, tab++,	"Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"%s\", \"%s\", \"%s\"", lib->name, vc_proj_pathname, project->proj_guid); _crlf(fp);
			if (inorder != NULL && inorder->count(inorder) > 0)
			{
				_sol_ftprintf(fp, tab++,	"ProjectSection(ProjectDependencies) = postProject"); _crlf(fp);

				if (vc90_solution_proj_dep(fp, inorder, tab, errp) == FALSE) ERR_OUT(errp);
				else Dz1Error_set(errp, 0);

				_sol_ftprintf(fp, --tab,	"EndProjectSection"); _crlf(fp);
			}
	 		_sol_ftprintf(fp, --tab,	"EndProject"); _crlf(fp);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t vc90_solution_test_proj(FILE *fp, GenEnvVisualStudio *vs_env, Dz1Str sln_path_abs, GenEnv *env, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (vs_env->test != NULL)
	{
		if (vc90_solution_proj(fp, vs_env->test, sln_path_abs, env->libs_test, tab, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
// emit Project
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// emit Libraries
static Dz1Error _vc90_solution_libs(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	FILE *fp = (FILE *)arg->dst;
	if (vc90_solution_proj(fp, p, arg->bias_path_abs, NULL, arg->tab, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return err;
}

static bool_t vc90_solution_libs(FILE *fp, GenArgs2LibraryRefIndex *inorder, Dz1Str sln_path_abs, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TextEmitArg arg = { fp, sln_path_abs, tab };
	if ((*errp = inorder->travel(inorder, _vc90_solution_libs, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// emit Libraries
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// _vc90_solution_conf_build
static bool_t _vc90_solution_conf_build_lib(FILE *fp, GenArgs2LibraryEntry *lib, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2VisualStudioList *projects = lib->projects;
	GenArgs2VisualStudioEntry *project = GenArgs2VisualStudioList_getProj(projects, GenArgs2VisualStudioVer_vc90);

	if (project == NULL) ERR_SET_OUT(errp, ENOENT);
	else
	{
		ProjectVcConf conf;
		for (conf = 0; conf < ProjectVcConf_max; conf++)
		{
			_sol_ftprintf(fp, tab,	"%s.%s|Win32.ActiveCfg = %s|Win32", project->proj_guid, ProjectVcConfStr(conf), ProjectVcConfStr(conf)); _crlf(fp);
			_sol_ftprintf(fp, tab, "%s.%s|Win32.Build.0 = %s|Win32", project->proj_guid, ProjectVcConfStr(conf), ProjectVcConfStr(conf)); _crlf(fp);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static Dz1Error __vc90_solution_conf_build_libs(void *ptr, GenArgs2LibraryEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	TextEmitArg *arg = (TextEmitArg *)ptr;
	FILE *fp = (FILE *)arg->dst;
	if (_vc90_solution_conf_build_lib(fp, p, arg->tab, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

static bool_t _vc90_solution_conf_build_libs(FILE *fp, GenArgs2LibraryRefIndex *inorder, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	TextEmitArg arg = { fp, NULL, tab };
	if ((*errp = inorder->travel(inorder, __vc90_solution_conf_build_libs, (void *)&arg)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _vc90_solution_conf_build(FILE *fp, GenEnv *env, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenEnvVisualStudio *vs_env = env->vs_env;
//	GenArgs2LibraryInfo *libs = env->libs;
	_sol_ftprintf(fp, tab++,	"GlobalSection(ProjectConfigurationPlatforms) = postSolution"); _crlf(fp);

	if (_vc90_solution_conf_build_lib(fp, vs_env->target, tab, errp) == FALSE) ERR_OUT(errp);
	else if (vs_env->test != NULL && _vc90_solution_conf_build_lib(fp, vs_env->test, tab, errp) == FALSE) ERR_OUT(errp);
	else if (_vc90_solution_conf_build_libs(fp, env->libs, tab, errp) == FALSE) ERR_OUT(errp);
	else if (_vc90_solution_conf_build_lib(fp, env->dimz_dz1, tab, errp) == FALSE) ERR_OUT(errp);
	else if (_vc90_solution_conf_build_lib(fp, env->codeconv, tab, errp) == FALSE) ERR_OUT(errp);
	else if (_vc90_solution_conf_build_lib(fp, vs_env->ptw_win, tab, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	_sol_ftprintf(fp, --tab,	"EndGlobalSection"); _crlf(fp);

	return errp->code == 0 ? TRUE : FALSE;
}
// _vc90_solution_conf_build
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// emit Solution
static void _vc90_solution_conf(FILE *fp, int tab)
{
	ProjectVcConf conf;
	_sol_ftprintf(fp, tab++,	"GlobalSection(SolutionConfigurationPlatforms) = preSolution"); _crlf(fp);
	for (conf = 0; conf < ProjectVcConf_max; conf++)
	{
		_sol_ftprintf(fp, tab, "%s|Win32 = %s|Win32", ProjectVcConfStr(conf), ProjectVcConfStr(conf)); _crlf(fp);
	}
	_sol_ftprintf(fp, --tab,	"EndGlobalSection"); _crlf(fp);
}

static void vc90_solution_global_property(FILE *fp, int tab)
{
	_sol_ftprintf(fp, tab++,	"GlobalSection(SolutionProperties) = preSolution"); _crlf(fp);
	_sol_ftprintf(fp, tab,			"HideSolutionNode = FALSE"); _crlf(fp);
	_sol_ftprintf(fp, --tab,	"EndGlobalSection"); _crlf(fp);
}

static bool_t vc90_solution_global(FILE *fp, GenEnv *env, int tab, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	_sol_ftprintf(fp, tab++,	"Global"); _crlf(fp);

	_vc90_solution_conf(fp, tab);
	if (_vc90_solution_conf_build(fp, env, tab, errp) == FALSE) ERR_OUT(errp);
	else 
	{
		vc90_solution_global_property(fp, tab);
		Dz1Error_set(errp, 0);
	}
	_sol_ftprintf(fp, --tab,	"EndGlobal"); _crlf(fp);
	return errp->code == 0 ? TRUE : FALSE;
}
bool_t vc90_solution(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	int tab = 0;

	GenEnvVisualStudio *vs_env = env->vs_env;
	// GenArgs2LibraryEntry *ptw_win = vs_env->ptw_win; // modified by gm 20230602 - unused var ptw_win

	_sol_ftprintf(fp, tab,		"Microsoft Visual Studio Solution File, Format Version 10.00"); _lf(fp, env->txt_mode);
	_sol_ftprintf(fp, tab,		"# Visual Studio 2008"); _lf(fp, env->txt_mode);

	if (vc90_solution_proj(fp, vs_env->target, work_path_abs, env->libs, tab, errp) == FALSE) ERR_OUT(errp);	// emit target
	else if (vc90_solution_test_proj(fp, vs_env, work_path_abs, env, tab, errp) == FALSE) ERR_OUT(errp);		// emit test
	else if (vc90_solution_libs(fp, env->libs, work_path_abs, tab, errp) == FALSE) ERR_OUT(errp);				// emit included libraries

	else if (vc90_solution_proj(fp, env->dimz_dz1, work_path_abs, NULL, tab, errp) == FALSE) ERR_OUT(errp);		// emit dimz_dz1
	else if (vc90_solution_proj(fp, env->codeconv, work_path_abs, NULL, tab, errp) == FALSE) ERR_OUT(errp);		// emit dimz_dz1
	else if (vc90_solution_proj(fp, vs_env->ptw_win, work_path_abs, NULL, tab, errp) == FALSE) ERR_OUT(errp);	// emit ptw_win

	else if (vc90_solution_global(fp, env, tab, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// emit Solution
///////////////////////////////////////////////////////////////////////////////

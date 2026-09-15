////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "code_gen_env.h"

////////////////////////////////////////////////////////////////////////////////
// GenEnvVisualStudio
GenEnvVisualStudio *GenEnvVisualStudio_new(GenArgs2LibraryEntry *target, 
										   Dz1Str target_guid, 
										   GenArgs2LibraryEntry *test, 
										   Dz1Str test_guid, 
										   GenArgs2LibraryEntry *ptw_win, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenEnvVisualStudio *__internal_ret = (GenEnvVisualStudio *)Dz1Calloc(sizeof(GenEnvVisualStudio), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenEnvVisualStudio_delAndSetNull, (void *)&__internal_ret);
		
		if (target_guid && (__internal_ret->target_guid = Dz1Str_clone(target_guid, errp)) == NULL) ERR_OUT(errp);
		else if (test_guid && (__internal_ret->test_guid = Dz1Str_clone(test_guid, errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->target = target;
			__internal_ret->test = test;
			__internal_ret->ptw_win = ptw_win;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenEnvVisualStudio_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GenEnvVisualStudio_purge(GenEnvVisualStudio *p)
{
	if (p == NULL) return;
	GenArgs2LibraryEntry_del(p->target);
	Dz1Str_del(p->target_guid);
	GenArgs2LibraryEntry_del(p->test);
	Dz1Str_del(p->test_guid);
	GenArgs2LibraryEntry_del(p->ptw_win);
}

void GenEnvVisualStudio_del(GenEnvVisualStudio *p)
{
	if (p == NULL) return;
	GenEnvVisualStudio_purge(p);
	Dz1Free(p);
}

// GenEnvVisualStudio
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenEnv
GenEnv *GenEnv_new(Dz1Str target_path_abs, 
				   u32_t gen_flags, 
				   GenArgs2Naming rule, 
				   Dz1GenTextMode txt_mode, 
				   GenArgs2LibraryEntry *dimz_dz1, 
				   GenArgs2LibraryEntry *codeconv, 
				   GenArgs2LibraryRefIndex *libs/*_ref*/, 
				   GenEnvVisualStudio *vs_env, 
				   TxtReplaceEnv *rp_env, Dz1Error *err)
{
	Dz1Error _err = DZ1_ERROR_INITIALIZER, *errp = err ? err : &_err;
	GenEnv *__internal_ret = (GenEnv *)Dz1Calloc(sizeof(GenEnv), 1, errp);
	if (__internal_ret == NULL) { ERR_SET_OUT(errp, ENOMEM); }
	else
	{
		pthread_cleanup_push(GenEnv_delAndSetNull, (void *)&__internal_ret);
		
		if (target_path_abs && (__internal_ret->target_path_abs = Dz1Str_clone(target_path_abs, errp)) == NULL) ERR_OUT(errp);
		else if ((__internal_ret->libs_test = GenArgs2LibraryRefIndex_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			__internal_ret->gen_flags = gen_flags;
			__internal_ret->rule = rule;
			__internal_ret->txt_mode = txt_mode;
			__internal_ret->dimz_dz1 = dimz_dz1;
			__internal_ret->codeconv = codeconv;
			__internal_ret->libs = libs;
			__internal_ret->vs_env = vs_env;
			__internal_ret->rp_env = rp_env;
			ERR_CLEAR(errp);
		}
		pthread_cleanup_pop(ERR_PROBE(errp)); // (GenEnv_delAndSetNull, (void *)&__internal_ret)
	}
	return __internal_ret;
}

void GenEnv_purge(GenEnv *p)
{
	if (p == NULL) return;
	Dz1Str_del(p->target_path_abs);
	GenArgs2LibraryEntry_del(p->dimz_dz1);
	GenArgs2LibraryEntry_del(p->codeconv);
	GenArgs2LibraryRefIndex_del(p->libs_test);
	GenEnvVisualStudio_del(p->vs_env);
	TxtReplaceEnv_del(p->rp_env);
}

void GenEnv_del(GenEnv *p)
{
	if (p == NULL) return;
	GenEnv_purge(p);
	Dz1Free(p);
}

// GenEnv
////////////////////////////////////////////////////////////////////////////////


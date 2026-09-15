#ifndef _DZ1_TDC_CODE_GEN_ENV_H_
#define _DZ1_TDC_CODE_GEN_ENV_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_task_gen_args.h"
#include "txt_replace_env.h"

////////////////////////////////////////////////////////////////////////////////
// GenEnvVisualStudio
typedef struct GenEnvVisualStudio
{
	GenArgs2LibraryEntry	*target;
	Dz1Str					 target_guid;
	GenArgs2LibraryEntry	*test;
	Dz1Str					 test_guid;
	GenArgs2LibraryEntry	*ptw_win;
} GenEnvVisualStudio;

DZ1_CPPLINK DZ1_DLLPORT GenEnvVisualStudio *GenEnvVisualStudio_new(GenArgs2LibraryEntry *target, 
																   Dz1Str target_guid, 
																   GenArgs2LibraryEntry *test, 
																   Dz1Str test_guid, 
																   GenArgs2LibraryEntry *ptw_win, Dz1Error *err);
static __inline__ GenEnvVisualStudio *GenEnvVisualStudio_gen(Dz1Error *err) { return GenEnvVisualStudio_new(NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GenEnvVisualStudio_purge(GenEnvVisualStudio *p);
DZ1_CPPLINK DZ1_DLLPORT void GenEnvVisualStudio_del(GenEnvVisualStudio *p);
static __inline__ void GenEnvVisualStudio_delAndSetNull(void *ptr)
{
	GenEnvVisualStudio **p = (GenEnvVisualStudio **)ptr;
	if (p) { GenEnvVisualStudio_del(*p); *p = NULL; }
}
// GenEnvVisualStudio
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// GenEnv
typedef struct GenEnv
{
	Dz1Str						 target_path_abs;
	u32_t						 gen_flags;
	GenArgs2Naming				 rule;
	Dz1GenTextMode				 txt_mode;
	GenArgs2LibraryEntry		*dimz_dz1;
	GenArgs2LibraryEntry		*codeconv;
	GenArgs2LibraryRefIndex		*libs;
	GenArgs2LibraryRefIndex		*libs_test;
	GenEnvVisualStudio			*vs_env;
	TxtReplaceEnv				*rp_env;
} GenEnv;

DZ1_CPPLINK DZ1_DLLPORT GenEnv *GenEnv_new(Dz1Str target_path_abs, 
										   u32_t gen_flags, 
										   GenArgs2Naming rule, 
										   Dz1GenTextMode txt_mode, 
										   GenArgs2LibraryEntry *dimz_dz1, 
										   GenArgs2LibraryEntry *codeconv, 
										   GenArgs2LibraryRefIndex *libs_ref, 
										   GenEnvVisualStudio *vs_env, 
										   TxtReplaceEnv *rp_env, Dz1Error *err);
static __inline__ GenEnv *GenEnv_gen(Dz1Error *err) { return GenEnv_new(NULL, 0, GenArgs2Naming_max, Dz1GenTextMode_max, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void GenEnv_purge(GenEnv *p);
DZ1_CPPLINK DZ1_DLLPORT void GenEnv_del(GenEnv *p);
static __inline__ void GenEnv_delAndSetNull(void *ptr)
{
	GenEnv **p = (GenEnv **)ptr;
	if (p) { GenEnv_del(*p); *p = NULL; }
}
// GenEnv
////////////////////////////////////////////////////////////////////////////////

#endif

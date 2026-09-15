#ifndef DZ1_TASK_GEN4VC_H
#define DZ1_TASK_GEN4VC_H

#include <dz1_task_gen_args.h>

DZ1_CPPLINK bool_t _get_relative_path(TCHAR *dst, size_t dst_sz, Dz1Str fromPath, Dz1Str toPath, Dz1Error *err);
DZ1_CPPLINK bool_t _load_proj_guid(TCHAR dst[40], Dz1Str lib_root_abs, Dz1Str middle_path, Dz1Str proj_file_name, GenArgs2VisualStudioVer ver, Dz1Error *err);
DZ1_CPPLINK Dz1Str _getRuledName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Str suffix_name, GenArgs2Naming flag, Dz1Error *err);
DZ1_CPPLINK Dz1Str _getStructureName(TCHAR *dst, size_t dst_size, Dz1Str src, Dz1Str suffix_name, Dz1Error *err);

DZ1_CPPLINK bool_t		 Dz1TaskGen2(GenArgs2 *args, Dz1Error *err);
DZ1_CPPLINK Dz1Error	 GenArgs2_toStream(GenArgs2 *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param);
DZ1_CPPLINK GenArgs2	*GenArgs2_fromStream(Dz1Stream *src, void *param, Dz1IOStreamEndian ed, Dz1Error *err);

typedef struct LoadProjectMap
{
	GenArgs2VisualStudioVer		 ver;
	Dz1Str						 branch_path;
	Dz1Str						 proj_ext;
} LoadProjectMap;
DZ1_CPPLINK LoadProjectMap *LoadProjectMap_find(GenArgs2VisualStudioVer ver);


#endif
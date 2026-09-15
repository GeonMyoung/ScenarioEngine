#ifndef DZ1_MFC_FILE_UTIL_H
#define DZ1_MFC_FILE_UTIL_H

#include <Dz1MfcFileUtilDef.h>

DZ1_CPPLINK void						 Dz1MfcFileEntry_ucase(Dz1MfcFileEntry *node);
DZ1_CPPLINK void						 Dz1MfcFileEntry_lcase(Dz1MfcFileEntry *node);

DZ1_CPPLINK bool_t						 Dz1MfcFileList_addDirEntry(Dz1MfcFileList *dst, Dz1DirEntry *entry, bool_t ucase, Dz1Error *err);
DZ1_CPPLINK Dz1MfcFileList				*Dz1MfcFileList_fromPath(Dz1Str path, bool_t ucase, Dz1Error *err);
DZ1_CPPLINK Dz1MfcFileEntry				*Dz1MfcFileList_findByNameExt(Dz1MfcFileList *list, Dz1Str name_ext);

DZ1_CPPLINK bool_t						 Dz1MfcFilesDelete(Dz1MfcFileOperDeleteData *data);
DZ1_CPPLINK bool_t						 Dz1MfcFileDelete(Dz1MfcFileOperDeleteEntry *file);

///////////////////////////////////////////////////////////////////////////////
// Rename
DZ1_CPPLINK Dz1MfcFileOperRenameEntry	*Dz1MfcFileOperRenameList_findByNameExt(Dz1MfcFileOperRenameList *list, Dz1Str name_ext);
DZ1_CPPLINK bool_t						 Dz1MfcFilesRename(Dz1MfcFileOperRenameData *data);
//DZ1_CPPLINK bool_t					 Dz1MfcFileRename(Dz1Str path, Dz1MfcFileOperRenameEntry *file);
// Rename
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Copy Data Util
DZ1_CPPLINK Dz1Error					 Dz1MfcFileOperCopyData_append(Dz1MfcFileOperCopyData *dst, Dz1Str file_name_ext);
DZ1_CPPLINK bool_t						 Dz1MfcFileOperCopyData_is_collision(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_param);
// Copy Data Util
///////////////////////////////////////////////////////////////////////////////

#define DZ1_FILE_COPY_PHASE_PREPARE							1

#define DZ1_FILE_COPY_PHASE_TRANSFER						2
#define		DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_START		1
#define		DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_CHUNK_DONE		2
#define		DZ1_FILE_COPY_PHASE_TRANSFER_FLAG_FILE_DONE			3

///////////////////////////////////////////////////////////////////////////////
// Copy
DZ1_CPPLINK bool_t						 Dz1MfcFilesCopy(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err);
DZ1_CPPLINK bool_t						 Dz1MfcFileCopy(Dz1Str src_path, Dz1Str dst_path, Dz1Str file_name_ext, Dz1MfcFileCopyOperCBF cb, void *cb_arg);
// Copy
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Move
DZ1_CPPLINK bool_t						 Dz1MfcFilesMove(Dz1MfcFileOperCopyData *data, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err);
DZ1_CPPLINK bool_t						 Dz1MfcFileMove(Dz1Str src_path, Dz1Str dst_path, Dz1Str file_name_ext, Dz1MfcFileCopyOperCBF cb, void *cb_arg, Dz1Error *err);
// Move
///////////////////////////////////////////////////////////////////////////////

#endif
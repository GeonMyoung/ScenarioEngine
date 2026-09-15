#ifndef DZ1_VFS_UTIL_H_LOCAL
#define DZ1_VFS_UTIL_H_LOCAL

#include <dz1_vfs_def.h>

DZ1_CPPLINK Dz1VfsAccess	*Dz1VfsHandleDirList_open(Dz1VfsHandleDirList *list, u32_t idx, Dz1StorageHandle *io, Dz1Error *err);
DZ1_CPPLINK Dz1Error		 Dz1VfsHandleDirList_close(Dz1VfsHandleDirList *list, Dz1VfsAccess *access);
DZ1_CPPLINK Dz1Error		 Dz1VfsHandleDirList_mkdir(Dz1VfsHandleDirList *list, Dz1VfsAccess *access,
													   Dz1Asn1UTF8Str *name, Dz1StorageHandle *io);
DZ1_CPPLINK Dz1Error		 Dz1VfsHandleDirList_chdir(Dz1VfsHandleDirList *list, Dz1VfsAccess *access,
													   Dz1Asn1UTF8Str *name, Dz1StorageHandle *io);
DZ1_CPPLINK Dz1Error		 Dz1VfsHandleDirList_rmdir(Dz1VfsHandleDirList *list, Dz1VfsAccess *access,
													   Dz1VfsHandleFileList *files);

DZ1_CPPLINK Dz1VfsAccess	*Dz1VfsHandleFileList_open(Dz1VfsHandleFileList *list,
													   Dz1VfsAccess *dir, Dz1Asn1UTF8Str *name,
													   Dz1VfsHandleDirList *dirs,
													   Dz1Error *err);

#endif
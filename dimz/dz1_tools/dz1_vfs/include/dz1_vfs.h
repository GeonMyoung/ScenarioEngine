#ifndef DZ1_VFS_H
#define DZ1_VFS_H

#include <dz1_vfs_def.h>

DZ1_CPPLINK Dz1Vfs *Dz1Vfs_open(str_t fn, Dz1Error *err);
DZ1_CPPLINK Dz1Vfs *Dz1Vfs_open2(str_t path, str_t name, Dz1Error *err);
#ifdef WIN32
DZ1_CPPLINK Dz1Vfs *Dz1VfsW_open(wstr_t fn, Dz1Error *err);
DZ1_CPPLINK Dz1Vfs *Dz1VfsW_open2(wstr_t path, wstr_t name, Dz1Error *err);
#endif

DZ1_CPPLINK void Dz1Vfs_close(Dz1Vfs *p);
static __inline__ void Dz1Vfs_closeAndsetNull(void *pptr)
{
	Dz1Vfs **p = (Dz1Vfs **)pptr;
	Dz1Vfs_close(*p); *p = NULL;
}

#endif
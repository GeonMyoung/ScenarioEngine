#ifndef DZ1_VFS_CODEC_H_LOCAL
#define DZ1_VFS_CODEC_H_LOCAL

#include <dz1_vfs_def.h>

///////////////////////////////////////////////////////////////////////////////
// FILE
DZ1_CPPLINK Dz1VfsFile	*Dz1VfsFile_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1VfsFile_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1VfsFile_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1Binary	*Dz1VfsFile_toStream(Dz1VfsFile *src, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1VfsFile	*Dz1VfsFile_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// FILE
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// DIR
DZ1_CPPLINK Dz1VfsDir	*Dz1VfsDir_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1VfsDir_enc(u8_t *dst, size_t size, void *_src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t		 Dz1VfsDir_dec(void *_dst, u8_t *src, size_t size, void *param, Dz1Error *err);

DZ1_CPPLINK Dz1Binary	*Dz1VfsDir_toStream(Dz1VfsDir *src, void *param, Dz1Error *err);
DZ1_CPPLINK Dz1VfsDir	*Dz1VfsDir_toStruct(Dz1Binary *src, void *param, Dz1Error *err);
// DIR
///////////////////////////////////////////////////////////////////////////////

#endif
#ifndef DZ1_VFS_CODEC_TEST_H
#define DZ1_VFS_CODEC_TEST_H

#include "src\dz1_vfs_codec.h"

DZ1_CPPLINK Dz1Error Dz1VfsFileCodec_test(Dz1VfsFile *src, bool_t verbose);
DZ1_CPPLINK Dz1Error Dz1VfsDirCodec_test(Dz1VfsDir *src, bool_t verbose);
//DZ1_CPPLINK Dz1Error Dz1VfsCodec_test(Dz1Vfs *src, bool_t verbose);

#endif
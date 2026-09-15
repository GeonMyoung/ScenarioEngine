#ifndef DZ_1_TASK_GEN_ARGS
#define DZ_1_TASK_GEN_ARGS

#include <dz1_io_stream.h>
#include "dz1_task_gen_args.h"
DZ1_CPPLINK ssize_t GenArgs2VisualStudioEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2VisualStudioEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2VisualStudioList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2VisualStudioList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2LibraryEntry_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2LibraryEntry_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2LibraryList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2LibraryList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2LibraryInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2LibraryInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2VisualStudio_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2VisualStudio_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t GenArgs2_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t GenArgs2_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#endif // DZ_1_TASK_GEN_ARGS

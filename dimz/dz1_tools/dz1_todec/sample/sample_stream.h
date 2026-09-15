#ifndef SAMPLE
#define SAMPLE

#include <dz1_io_stream.h>
#include "sample.h"
DZ1_CPPLINK ssize_t MyData_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t MyData_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t StructSample_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t StructSample_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t StructSampleOther_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t StructSampleOther_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t StructSampleList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t StructSampleList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t UnionSample_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSample_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSampleIndication_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSampleIndication_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSampleOther_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSampleOther_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t UnionSampleList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t UnionSampleList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#endif // SAMPLE

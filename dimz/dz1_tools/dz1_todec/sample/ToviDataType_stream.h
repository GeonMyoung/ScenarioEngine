#ifndef TOVI_DATA_TYPE
#define TOVI_DATA_TYPE

#include <dz1_io_stream.h>
#include "ToviDataType.h"
DZ1_CPPLINK ssize_t TovisTypeEnumMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeEnumMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeEnumMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeEnumInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeEnumInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeStructMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeStructMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeStructMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeStructMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeStructMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeStructMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeStructInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeStructInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeUnionMemb_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionMemb_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeUnionMembList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionMembList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeUnionMembInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionMembInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeUnionInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeUnionInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeArrayCmpInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeArrayCmpInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeArrayElement_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeArrayElement_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeArrayInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeArrayInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeArrayInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeArrayInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisTypeNamedInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeNamedInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeNamedInfoIndicator_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisTypeNamedInfoIndicator_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataInfo_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataInfo_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataType_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataType_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataTypeList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataTypeList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataTypeRefList_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataTypeRefList_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataTypeSeq_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataTypeSeq_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataObject_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataObject_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataObjects_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataObjects_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

DZ1_CPPLINK ssize_t TovisDataObjectsRef_read(void *_dst, Dz1Stream *src, Dz1IOStreamEndian ed, Dz1StreamCallStk *param, Dz1Error *err);
DZ1_CPPLINK ssize_t TovisDataObjectsRef_write(Dz1Stream *dst, void *_src, Dz1IOStreamEndian ed, void *param, Dz1Error *err);

#endif // TOVI_DATA_TYPE

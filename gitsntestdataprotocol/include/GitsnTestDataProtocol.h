#ifndef PRJ22_TEST_DATA_PROTOCOL_H
#define PRJ22_TEST_DATA_PROTOCOL_H

#include <GitsnTestDataProtocolDef.h>

// declare library functions here


DZ1_CPPLINK GitsnTestDataFrames* GitsnTestDataProtocol_convertToDataFrames(Dz1Binary* src, Dz1Error* err);
DZ1_CPPLINK Dz1Binary* GitsnTestDataProtocol_getPayloadFromDataFrames(GitsnTestDataFrames* src, Dz1Error* err);

DZ1_CPPLINK Dz1Binary *GitsnTestDataFrame_encode(GitsnTestDataFrame *src, Dz1Error *err);
DZ1_CPPLINK GitsnTestDataFrame* GitsnTestDataFrame_decode(Dz1Binary* src, Dz1Error* err);



// decode

#endif // PRJ22_TEST_DATA_PROTOCOL_H

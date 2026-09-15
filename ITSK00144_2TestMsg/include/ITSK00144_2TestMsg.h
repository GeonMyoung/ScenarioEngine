#ifndef ITSK00144_2_TEST_MSG_H
#define ITSK00144_2_TEST_MSG_H

#include <ITSK00144_2TestMsgDef.h>

// declare library functions here

DZ1_CPPLINK Dz1Binary* ITSK00144_2ProtocolFrame_encode(ITSK00144_2ProtocolFrame* src, Dz1Error* err);
DZ1_CPPLINK ssize_t ITSK00144_2ProtocolFrame_write(Dz1Stream* dst, ITSK00144_2ProtocolFrame* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t ITSK00144_2ProtocolFrameContext_read(ITSK00144_2ProtocolFrameContext* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_decode(Dz1Binary* src, Dz1Error* err);


DZ1_CPPLINK ITSK00144_2ProtocolFrameContext* ITSK00144_2ProtocolFrameContext_decode(Dz1Binary* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


DZ1_CPPLINK ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(I2XTrafficSafetyDeviceSerialNo* id, u8_t seq, ITSK00144_2DataPresent present, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ITSK00144_2ProtocolFrame* ITSK00144_2ProtocolFrame_fromITSK00144_2Data(I2XTrafficSafetyDeviceSerialNo* id, u8_t seq, ITSK00144_2Data* data, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


#endif // ITSK00144_2_TEST_MSG_H

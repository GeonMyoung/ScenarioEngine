#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_H_LOCAL
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_H_LOCAL

#include <TrafficSignalControllerTestMsg.h>

DZ1_CPPLINK ssize_t CrossControlCmd_write(Dz1Stream* dst, CrossControlCmd* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t CrossControlCmd_read(CrossControlCmd* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


DZ1_CPPLINK ssize_t CrossStatusBasicInfo_write(Dz1Stream* dst, CrossStatusBasicInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t CrossStatusBasicInfo_read(CrossStatusBasicInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


DZ1_CPPLINK ssize_t CrossStatusExtInfo_r27_write(Dz1Stream* dst, CrossStatusExtInfo_r27* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t CrossStatusExtInfo_r27_read(CrossStatusExtInfo_r27* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t DetectorInfo_write(Dz1Stream* dst, DetectorInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t DetectorInfo_read(DetectorInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t SignalPhaseInfoDown_r27_write(Dz1Stream* dst, SignalPhaseInfoDown_r27* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t SignalPhaseInfoDown_r27_read(SignalPhaseInfoDown_r27* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t SignalPhaseInfoUp_write(Dz1Stream* dst, SignalPhaseInfoUp* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t SignalPhaseInfoUp_read(SignalPhaseInfoUp* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t ClockInfo_write(Dz1Stream* dst, ClockInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t ClockInfo_read(ClockInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t SpecialCommandInfo_write(Dz1Stream* dst, SpecialCommandInfo* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t SpecialCommandInfo_read(SpecialCommandInfo* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t SpecialCommandPPCNumberList_write(Dz1Stream* dst, SpecialCommandPPCNumberList* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t SpecialCommandPPCNumberList_read(SpecialCommandPPCNumberList* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK ssize_t FirmwareUpgradeData_write(Dz1Stream* dst, FirmwareUpgradeData* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t FirmwareUpgradeData_read(FirmwareUpgradeData* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


DZ1_CPPLINK ssize_t FirmwareUpgradeError_write(Dz1Stream* dst, FirmwareUpgradeError* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t FirmwareUpgradeError_read(FirmwareUpgradeError* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);



#endif // !TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_H_LOCAL



#ifndef TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_FRAME_H
#define TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_FRAME_H

#include <TrafficSignalControllerTestMsgFrameDef.h>

// TrafficSignalControllerTestMsgFrameContext
DZ1_CPPLINK ssize_t TrafficSignalControllerTestMsgFrameContext_write(Dz1Stream* dst, TrafficSignalControllerTestMsgFrameContext* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t TrafficSignalControllerTestMsgFrameContext_read(TrafficSignalControllerTestMsgFrameContext* dst, Dz1Stream* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

DZ1_CPPLINK Dz1Binary*									TrafficSignalControllerTestMsgFrameContext_encode(TrafficSignalControllerTestMsgFrameContext* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrameContext* TrafficSignalControllerTestMsgFrameContext_decode(Dz1Binary* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);


// TrafficSignalControllerTestMsgFrame
DZ1_CPPLINK ssize_t										TrafficSignalControllerTestMsgFrame_write(Dz1Stream* dst, TrafficSignalControllerTestMsgFrame* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK ssize_t										TrafficSignalControllerTestMsgFrame_read(TrafficSignalControllerTestMsgFrame *dst, Dz1Stream* src, Dz1IOStreamEndian ed, void *param, Dz1Error* err);
DZ1_CPPLINK Dz1Binary*									TrafficSignalControllerTestMsgFrame_encode(TrafficSignalControllerTestMsgFrame* src, Dz1Error* err);


DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromCrossControlInformation(CrossControlInformation* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromCrossIndicator(CrossIndicator* src, Dz1IOStreamEndian ed, TrafficSignalControllerRequestPresent present, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromSignalPhaseInformationDownload(SignalPhaseInformationDownload* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromClockInformationDownload(ClockInformationDownload* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromSpecialCommandInformation(SpecialCommandInformation* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);
DZ1_CPPLINK TrafficSignalControllerTestMsgFrame*		TrafficSignalControllerTestMsgFrame_fromFirmwareUpgradeCommand(FirmwareUpgradeCommand* src, Dz1IOStreamEndian ed, void* param, Dz1Error* err);

#endif // !TRAFFIC_SIGNAL_CONTROLLER_TEST_MSG_FRAME_H

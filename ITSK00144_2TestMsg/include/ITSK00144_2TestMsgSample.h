#ifndef ITSK_00144_2_TEST_MSG_SAMPLE_H
#define ITSK_00144_2_TEST_MSG_SAMPLE_H

#include <ITSK00144_2TestMsgDef.h>



DZ1_CPPLINK_VAR I2XTrafficSafetyDeviceLinkUnitStatus* sample_i2x_traffic_safety_device_link_unit_status;
DZ1_CPPLINK_VAR I2XTrafficSafetyDeviceStatusInfo* sample_i2x_traffic_safety_device_status_info;
DZ1_CPPLINK_VAR I2XTrafficSafetyDeviceList* sample_i2x_traffic_safety_device_list;

DZ1_CPPLINK bool_t ITSK00144_2TestMsg_initSample(Dz1Error* err);
DZ1_CPPLINK void ITSK00144_2TestMsg_clearSample(Dz1Error* err);


#endif // !ITSK_00144_2_TEST_MSG_SAMPLE_H

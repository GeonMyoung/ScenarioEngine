#ifndef GITSN_ASN_UTIL_SAMPLE_MSG_H
#define GITSN_ASN_UTIL_SAMPLE_MSG_H

#include <GitsnAsnUtil.h>

DZ1_CPPLINK_VAR MapData* sample_map;										// DSRCmsgID = 18
DZ1_CPPLINK_VAR SPAT* sample_spat;											// DSRCmsgID = 19
DZ1_CPPLINK_VAR BasicSafetyMessage* sample_bsm;								// DSRCmsgID = 20

DZ1_CPPLINK_VAR EmergencyVehicleAlert* sample_eva;							// DSRCmsgID = 22

DZ1_CPPLINK_VAR	ProbeVehicleData* sample_pvd;								// DSRCmsgID = 26
DZ1_CPPLINK_VAR RoadSideAlert* sample_rsa;									// DSRCmsgID = 27

DZ1_CPPLINK_VAR RTCMcorrections* sample_rtcm;								// DSRCmsgID = 28

DZ1_CPPLINK_VAR	SignalRequestMessage *sample_srm;							// DSRCmsgID = 29
DZ1_CPPLINK_VAR	SignalStatusMessage *sample_ssm;								// DSRCmsgID = 30

DZ1_CPPLINK_VAR TravelerInformation* sample_tim;							// DSRCmsgID = 31

DZ1_CPPLINK_VAR PersonalSafetyMessage* sample_psm;							// DSRCmsgID = 32

DZ1_CPPLINK_VAR SensorDataSharingMessage* sample_sdsm;						// DSRCmsgID = 41

DZ1_CPPLINK_VAR TLS* sample_tls;											// DSRCmsgID = 50; 
DZ1_CPPLINK_VAR TrafficLightStatusMessage* sample_tlsm;						// DSRCmsgID = 50; 



DZ1_CPPLINK bool_t GitsnAsnUtil_initSample(Dz1Error* err);

#endif // !GITSN_ASN_UTIL_SAMPLE_MSG_H

#ifndef TECHNICAL_REGULATION1_MSG_STRUCT_API_H
#define TECHNICAL_REGULATION1_MSG_STRUCT_API_H

#include <Iso14827TestMsgUtil.h>
#include <TechnicalRegulation1EAM.h>
#include <TechnicalRegulation1EAMDz1.h>
#include "TechnicalRegulation1Def.h"
#include "TechnicalRegulation1DefJson.h"

#define TECHNICAL_REGULATION1_EAM_PATH_101		Dz1T("current_link_state_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_102		Dz1T("event_identity_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_103		Dz1T("incident_identity_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_104		Dz1T("incident_conditions_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_105		Dz1T("roadway_surface_status_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_106		Dz1T("weather_information_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_107		Dz1T("link_roadway_geometry_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_108		Dz1T("probe_vehicle_detection_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_109		Dz1T("detector_collection_list.json.txt")
#define TECHNICAL_REGULATION1_EAM_PATH_110		Dz1T("extention_comm_pdu_list.json.txt")


DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation1MsgSet[];
DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI TechnicalRegulation1_PolicePrj4C2CMsgSet[];

DZ1_CPPLINK_VAR Iso14827TestMsgStructAPI ITSK00100_3MsgSet[];


#endif // TECHNICAL_REGULATION1_MSG_STRUCT_API_H

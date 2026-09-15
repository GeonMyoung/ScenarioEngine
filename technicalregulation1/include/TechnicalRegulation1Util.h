#ifndef TECHNICAL_REGULATION1_UTIL_H
#define TECHNICAL_REGULATION1_UTIL_H


#include <TechnicalRegulation1EAMDz1.h>
#include <TechnicalRegulation1Def.h>
#include <TechnicalRegulation1DefJson.h>



DZ1_CPPLINK CurrentLinkStateList *CurrentLinkStateList_fromDimz(Dz1CurrentLinkStateResponse* src, Dz1Error* err);
DZ1_CPPLINK EventIdentityList* EventIdentityList_fromDimz(Dz1EventIdentityResponse* src, Dz1Error* err);
DZ1_CPPLINK IncidentIdentityList* IncidentIdentityList_fromDimz(Dz1IncidentIdentityResponse* src, Dz1Error* err);
DZ1_CPPLINK IncidentConditionsList* IncidentConditionsList_fromDimz(Dz1IncidentConditionsResponse* src, Dz1Error* err);
DZ1_CPPLINK RoadwaySurfaceStatusList* RoadwaySurfaceStatusList_fromDimz(Dz1RoadwaySurfaceStatusResponse* src, Dz1Error* err);
DZ1_CPPLINK WeatherInformationList* WeatherInformationList_fromDimz(Dz1WeatherInformationResponse* src, Dz1Error* err);
DZ1_CPPLINK LinkRoadwayGeometryList* LinkRoadwayGeometryList_fromDimz(Dz1LinkRoadwayGeometryResponse* src, Dz1Error* err);
DZ1_CPPLINK ProbeVehicleDetectionList* ProbeVehicleDetectionList_fromDimz(Dz1ProbeVehicleDetectionResponse* src, Dz1Error* err);
DZ1_CPPLINK DetectorCollectionList* DetectorCollectionList_fromDimz(Dz1DetectorCollectionResponse* src, Dz1Error* err);
DZ1_CPPLINK ExtentionCommPDUList* ExtentionCommPDUList_fromDimz(Dz1ExtentionCommPDUResponse* src, Dz1Error* err);


#endif // !TECHNICAL_REGULATION1_UTIL_H

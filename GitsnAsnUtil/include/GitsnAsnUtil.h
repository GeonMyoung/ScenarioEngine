#ifndef GITSN_ASN_UTIL_H
#define GITSN_ASN_UTIL_H

#include <GitsnAsnUtilDef.h>
#include <GitsnAsn1.h>
#include <dz1_gasn_support.h>
// declare library functions here


#define _gitsn_asn_util_decode_eam(struct_name)\
static bool_t struct_name##_uper_decode(ASN1WorkSpace* ws, Dz1Binary* src, void *asn_ptr, Dz1Error* errp)\
{\
	struct_name *asn = (struct_name *)asn_ptr;\
	size_t consume_sz = 0;\
	memset(asn_ptr, 0, sizeof(struct_name));\
	ASN1_Save_WORKSPACE(ws, src->data, src->size);\
	ws->dataSize = src->size;\
	if (ASN1_PER_UNAlign_Dec_##struct_name(ws, asn) < 0) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		consume_sz = ws->buffer.current - ws->buffer.data;\
		Dz1Error_set(errp, 0);\
	}\
	if (errp->code == 0)\
	{\
	}\
	return ERR_IS_SUCCESS(errp);\
}\

#define _gitsn_get_uper_encode_declare(struct_name)\
static Dz1Binary* struct_name##_get_uper_encoded(struct_name *ptr, Dz1Error *errp)\
{\
	Dz1Binary* ret = NULL;\
	ASN1WorkSpace ws;\
	ASN1_INIT_WS_INFO(&ws);\
	pthread_cleanup_push(ASN1_INIT_WS_INFO_cancel, (void*)&ws);\
	if (ASN1_PER_UNAlign_Enc_##struct_name(&ws, ptr) < 0) ERR_SET_OUT(errp, EFAULT);\
	else\
	{\
		if (errp->code == 0)\
		{\
			if ((ret = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&ws), ASN1WorkSpace_getEncodedSize(&ws, Dz1Asn1Codec_uper), errp)) == NULL) ERR_OUT(errp);\
			else Dz1Error_set(errp, 0);\
		}\
	}\
	pthread_cleanup_pop(1);\
	return ret;\
}

_gitsn_get_uper_encode_declare(MapData);
_gitsn_get_uper_encode_declare(SPAT);
_gitsn_get_uper_encode_declare(BasicSafetyMessage);
_gitsn_get_uper_encode_declare(EmergencyVehicleAlert);
_gitsn_get_uper_encode_declare(ProbeVehicleData);
_gitsn_get_uper_encode_declare(RoadSideAlert);
_gitsn_get_uper_encode_declare(RTCMcorrections);
_gitsn_get_uper_encode_declare(SignalRequestMessage);
_gitsn_get_uper_encode_declare(SignalStatusMessage);
_gitsn_get_uper_encode_declare(TravelerInformation);
_gitsn_get_uper_encode_declare(PersonalSafetyMessage);
_gitsn_get_uper_encode_declare(SensorDataSharingMessage);
_gitsn_get_uper_encode_declare(TLS);
_gitsn_get_uper_encode_declare(TrafficLightStatusMessage);

_gitsn_asn_util_decode_eam(MapData);
_gitsn_asn_util_decode_eam(SPAT);
_gitsn_asn_util_decode_eam(BasicSafetyMessage);
_gitsn_asn_util_decode_eam(EmergencyVehicleAlert);
_gitsn_asn_util_decode_eam(ProbeVehicleData);
_gitsn_asn_util_decode_eam(RoadSideAlert);
_gitsn_asn_util_decode_eam(RTCMcorrections);
_gitsn_asn_util_decode_eam(SignalRequestMessage);
_gitsn_asn_util_decode_eam(SignalStatusMessage);
_gitsn_asn_util_decode_eam(TravelerInformation);
_gitsn_asn_util_decode_eam(PersonalSafetyMessage);
_gitsn_asn_util_decode_eam(SensorDataSharingMessage);
_gitsn_asn_util_decode_eam(TLS);
_gitsn_asn_util_decode_eam(TrafficLightStatusMessage);


// convert util
// DSRC 
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_BasicSafetyMessageFromASN(BasicSafetyMessage* src, Gitsn_BasicSafetyMessage* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_MapDataFromASN(MapData* src, Gitsn_MapData* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_ProbeVehicleDataFromASN(ProbeVehicleData* src, Gitsn_ProbeVehicleData* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_SPATFromASN(SPAT* src, Gitsn_SPAT* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_RoadSideAlertFromASN(RoadSideAlert* src, Gitsn_RoadSideAlert* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_TravelerInformationFromASN(TravelerInformation* src, Gitsn_TravelerInformation* dst, Dz1Error* err);
// SDSM
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_SensorDataSharingMessageFromASN(SensorDataSharingMessage* src, Gitsn_SensorDataSharingMessage* dst, Dz1Error* err);
// TLS 
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_TLSFromASN(TLS* src, Gitsn_TLS* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_TrafficLightStatusMessageFromASN(TrafficLightStatusMessage* src, Gitsn_TrafficLightStatusMessage* dst, Dz1Error* err);

DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_EmergencyVehicleAlertFromASN(EmergencyVehicleAlert* src, Gitsn_EmergencyVehicleAlert* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_RTCMcorrectionsFromASN(RTCMcorrections* src, Gitsn_RTCMcorrections* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_SignalRequestMessageFromASN(SignalRequestMessage* src, Gitsn_SignalRequestMessage* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_SignalStatusMessageFromASN(SignalStatusMessage* src, Gitsn_SignalStatusMessage* dst, Dz1Error* err);
DZ1_CPPLINK bool_t GitsnAsnUtil_Gitsn_PersonalSafetyMessageFromASN(PersonalSafetyMessage* src, Gitsn_PersonalSafetyMessage* dst, Dz1Error* err);


DZ1_CPPLINK Dz1Binary* GitsnAsnUtil_getValueFromMessageFrame(Dz1Binary* src, int* msg_id, Dz1Error* errp);

#endif // GITSN_ASN_UTIL_H

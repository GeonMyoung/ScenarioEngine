#ifndef _CONFORMANCE2_H_
#define _CONFORMANCE2_H_

#include "BER/ASN1bersrc.h"
#include "IO/ASN1IO.h"
#include "MEM/mpool.h"
#include "OS/ASN1_Sys.h"
#include "TOOL/ASN1Tool.h"
#include "TYPE/ASN1_Type.h"



/********************************************************
*NetworkInfo                                            *
********************************************************/
struct NetworkInfo {
	OCTETSTRING ipAddress;
	INTEGER servicePort;
	OCTETSTRING providerServiceContext;
};
#ifndef STRUC_NetworkInfo
#define STRUC_NetworkInfo
typedef struct NetworkInfo NetworkInfo;

#endif

ASN1_CPPLINK int ASN1_Print_NetworkInfo(NetworkInfo* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_NetworkInfo_ipAddress(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_NetworkInfo_servicePort(ASN1WorkSpace* workspace, NetworkInfo* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_NetworkInfo_providerServiceContext(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_NetworkInfo_ipAddress(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_NetworkInfo_servicePort(ASN1WorkSpace* workspace, NetworkInfo* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_NetworkInfo_providerServiceContext(ASN1WorkSpace* workspace, NetworkInfo* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_NetworkInfo(ASN1WorkSpace* workspace, NetworkInfo* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommTxPDU                                              *
********************************************************/

#ifndef STRUC_NetworkInfo
#define STRUC_NetworkInfo
typedef struct NetworkInfo NetworkInfo;
#endif
struct CommTxPDU {
	int DEF_CommTxPDU_ipAddressServicePort;
	int DEF_CommTxPDU_signature;
	int DEF_CommTxPDU_payloadType;
	int DEF_CommTxPDU_txPower;
	int DEF_CommTxPDU_txDataRate;
	int DEF_CommTxPDU_channelNumberHdrExt;
	int DEF_CommTxPDU_dataRateHdrExt;
	int DEF_CommTxPDU_txPowerHdrExt;
	INTEGER index;
	INTEGER psid;
	INTEGER priority;
	INTEGER channel;
	INTEGER txInterval;
	NetworkInfo* ipAddressServicePort;/* optional */
	GeneralizedTime deliveryStart;
	GeneralizedTime deliveryStop;
	BOOLEAN signature;/* optional */
	INTEGER payloadType;/* optional */
	OCTETSTRING payload;
	INTEGER txPower;/* optional */
	INTEGER txDataRate;/* optional */
	BOOLEAN channelNumberHdrExt;/* optional */
	BOOLEAN dataRateHdrExt;/* optional */
	BOOLEAN txPowerHdrExt;/* optional */
};
#ifndef STRUC_CommTxPDU
#define STRUC_CommTxPDU
typedef struct CommTxPDU CommTxPDU;

#endif

ASN1_CPPLINK int ASN1_Print_CommTxPDU(CommTxPDU* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_index(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_psid(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_priority(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_channel(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_txInterval(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_ipAddressServicePort(ASN1WorkSpace* workspace, CommTxPDU* value, NetworkInfo* user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_deliveryStart(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_deliveryStop(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32 _TimeZoneInSecond, ASNINT32 _second, ASNINT32 _exponent);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_signature(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_payloadType(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_payload(ASN1WorkSpace* workspace, CommTxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_txPower(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_txDataRate(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_channelNumberHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_dataRateHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDU_txPowerHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_index(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_psid(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_priority(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_channel(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_txInterval(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_ipAddressServicePort(ASN1WorkSpace* workspace, CommTxPDU* value, NetworkInfo** user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_deliveryStart(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_deliveryStop(ASN1WorkSpace* workspace, CommTxPDU* value, struct tm* user_value, ASNINT32* _TimeZoneInSecond, ASNINT32* _second, ASNINT32* _exponent);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_signature(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_payloadType(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_payload(ASN1WorkSpace* workspace, CommTxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_txPower(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_txDataRate(ASN1WorkSpace* workspace, CommTxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_channelNumberHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_dataRateHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDU_txPowerHdrExt(ASN1WorkSpace* workspace, CommTxPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_BER_Enc_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommTxPDU(ASN1WorkSpace* workspace, CommTxPDU* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommTxPDURequest                                       *
********************************************************/
#ifndef STRUC_CommTxPDURequest
#define STRUC_CommTxPDURequest
typedef UTF8Str CommTxPDURequest;
#endif

ASN1_CPPLINK int ASN1_Print_CommTxPDURequest(CommTxPDURequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommTxPDURequest(ASN1WorkSpace* workspace, CommTxPDURequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommTxPDUResponse                                      *
********************************************************/

#ifndef STRUC_CommTxPDU
#define STRUC_CommTxPDU
typedef struct CommTxPDU CommTxPDU;
#endif
#ifndef STRUC_CommTxPDUResponse
#define STRUC_CommTxPDUResponse
typedef ASN1List CommTxPDUResponse;
#endif
ASN1_CPPLINK int ASN1_Print_CommTxPDUResponse(CommTxPDUResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CommTxPDUResponse_CommTxPDUResponse_pdata(ASN1WorkSpace* workspace, CommTxPDUResponse* value, CommTxPDU* user_value);
ASN1_CPPLINK int ASN1_GET_CommTxPDUResponse_CommTxPDUResponse_pdata(ASN1WorkSpace* workspace, CommTxPDUResponse* value, CommTxPDU** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommTxPDUResponse(ASN1WorkSpace* workspace, CommTxPDUResponse* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommRxPDU                                              *
********************************************************/
struct CommRxPDU {
	int DEF_CommRxPDU_peerAddress;
	int DEF_CommRxPDU_signed;
	int DEF_CommRxPDU_payloadType;
	INTEGER psid;
	INTEGER channel;
	INTEGER rcpi;
	OCTETSTRING peerAddress;/* optional */
	BOOLEAN sign;/* optional */
	INTEGER payloadType;/* optional */
	OCTETSTRING payload;
};
#ifndef STRUC_CommRxPDU
#define STRUC_CommRxPDU
typedef struct CommRxPDU CommRxPDU;

#endif

ASN1_CPPLINK int ASN1_Print_CommRxPDU(CommRxPDU* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_psid(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_channel(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_rcpi(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_peerAddress(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_signed(ASN1WorkSpace* workspace, CommRxPDU* value, BOOLEAN user_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_payloadType(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER user_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDU_payload(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8* user_value, ASNUINT32 user_value_length);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_psid(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_channel(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_rcpi(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_peerAddress(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_signed(ASN1WorkSpace* workspace, CommRxPDU* value, BOOLEAN* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_payloadType(ASN1WorkSpace* workspace, CommRxPDU* value, INTEGER* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDU_payload(ASN1WorkSpace* workspace, CommRxPDU* value, ASNUINT8** user_value, ASNUINT32* user_value_length);
ASN1_CPPLINK int ASN1_BER_Enc_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommRxPDU(ASN1WorkSpace* workspace, CommRxPDU* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommRxPDURequest                                       *
********************************************************/
#ifndef STRUC_CommRxPDURequest
#define STRUC_CommRxPDURequest
typedef UTF8Str CommRxPDURequest;
#endif

ASN1_CPPLINK int ASN1_Print_CommRxPDURequest(CommRxPDURequest* value, int tab_value);
ASN1_CPPLINK int ASN1_BER_Enc_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommRxPDURequest(ASN1WorkSpace* workspace, CommRxPDURequest* value, int length, ASN1TagType tagFlag);

/********************************************************
*CommRxPDUResponse                                      *
********************************************************/

#ifndef STRUC_CommRxPDU
#define STRUC_CommRxPDU
typedef struct CommRxPDU CommRxPDU;
#endif
#ifndef STRUC_CommRxPDUResponse
#define STRUC_CommRxPDUResponse
typedef ASN1List CommRxPDUResponse;
#endif
ASN1_CPPLINK int ASN1_Print_CommRxPDUResponse(CommRxPDUResponse* value, int tab_value);
ASN1_CPPLINK int ASN1_SET_CommRxPDUResponse_CommRxPDUResponse_pdata(ASN1WorkSpace* workspace, CommRxPDUResponse* value, CommRxPDU* user_value);
ASN1_CPPLINK int ASN1_GET_CommRxPDUResponse_CommRxPDUResponse_pdata(ASN1WorkSpace* workspace, CommRxPDUResponse* value, CommRxPDU** user_value);
ASN1_CPPLINK int ASN1_BER_Enc_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, ASN1TagType tagFlag);
ASN1_CPPLINK int ASN1_BER_Dec_CommRxPDUResponse(ASN1WorkSpace* workspace, CommRxPDUResponse* value, int length, ASN1TagType tagFlag);

#endif

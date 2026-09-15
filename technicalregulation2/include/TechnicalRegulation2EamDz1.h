#ifndef _DZ1_TDC_CONFORMANCE2_EAM_H_
#define _DZ1_TDC_CONFORMANCE2_EAM_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"
#include "dz1_asn1_support.h"

#include "TechnicalRegulation2Eam.h"
////////////////////////////////////////////////////////////////////////////////
// Dz1CommTxPDU
struct Dz1NetworkInfo;

typedef struct Dz1CommTxPDU
{
	u32_t                  index;
	u32_t                  psid;
	u8_t                   priority;
	u8_t                   channel;
	u16_t                  txInterval;
	struct Dz1NetworkInfo* ipAddressServicePort;
	Dz1TimeVal* deliveryStart;
	Dz1TimeVal* deliveryStop;
	bool_t* signature;
	s64_t* payloadType;
	Dz1Asn1OctetStr* payload;
	s8_t* txPower;
	u8_t* txDataRate;
	bool_t* channelNumberHdrExt;
	bool_t* dataRateHdrExt;
	bool_t* txPowerHdrExt;
} Dz1CommTxPDU;

DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDU* Dz1CommTxPDU_new(u32_t index,
	u32_t psid,
	u8_t priority,
	u8_t channel,
	u16_t txInterval,
	Dz1TimeVal* deliveryStart,
	Dz1TimeVal* deliveryStop,
	Dz1Asn1OctetStr* payload, Dz1Error* err);
static __inline__ Dz1CommTxPDU* Dz1CommTxPDU_gen(Dz1Error* err) { return Dz1CommTxPDU_new(0, 0, 0, 0, 0, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDU* Dz1CommTxPDU_clone(Dz1CommTxPDU* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDU_del(Dz1CommTxPDU* p);
static __inline__ void Dz1CommTxPDU_delAndSetNull(void* ptr)
{
	Dz1CommTxPDU** p = (Dz1CommTxPDU**)ptr;
	Dz1CommTxPDU_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDU_dump(Dz1CommTxPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDU_fdump(FILE* fp, Dz1CommTxPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommTxPDU_fromASN(Dz1CommTxPDU* dst, CommTxPDU* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDU* Dz1CommTxPDU_newFromASN(CommTxPDU* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommTxPDU_toASN(CommTxPDU* dst, Dz1CommTxPDU* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT CommTxPDU* Dz1CommTxPDU_toNewASN(Dz1CommTxPDU* src, ASN1WorkSpace* ws, Dz1Error* err);

// Dz1CommTxPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommTxPDURequest
typedef Dz1Asn1UTF8Str Dz1CommTxPDURequest;

#define Dz1CommTxPDURequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1CommTxPDURequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1CommTxPDURequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1CommTxPDURequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommTxPDUResponse
typedef struct Dz1CommTxPDUResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1CommTxPDUResponse* p, Dz1CommTxPDU* data);
	Dz1CommTxPDU** (*get_array)(struct Dz1CommTxPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1CommTxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommTxPDU* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1CommTxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommTxPDU* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1CommTxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommTxPDU* entry), void* ptr);
	unsigned int (*count)(struct Dz1CommTxPDUResponse* p);
} Dz1CommTxPDUResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_new(Dz1Error* err);
static __inline__ Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_gen(Dz1Error* err) { return Dz1CommTxPDUResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_clone(Dz1CommTxPDUResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDUResponse_del(Dz1CommTxPDUResponse* p);
static __inline__ void Dz1CommTxPDUResponse_delAndSetNull(void* ptr)
{
	Dz1CommTxPDUResponse** p = (Dz1CommTxPDUResponse**)ptr;
	Dz1CommTxPDUResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDUResponse_dump(Dz1CommTxPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommTxPDUResponse_fdump(FILE* fp, Dz1CommTxPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommTxPDUResponse_fromASN(Dz1CommTxPDUResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CommTxPDUResponse* Dz1CommTxPDUResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommTxPDUResponse_toASN(ASN1List* dst, Dz1CommTxPDUResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1CommTxPDUResponse_toNewASN(Dz1CommTxPDUResponse* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1CommTxPDUResponse
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1NetworkInfo
typedef struct Dz1NetworkInfo
{
	Dz1Asn1OctetStr* ipAddress;
	u16_t            servicePort;
	Dz1Asn1OctetStr* providerServiceContext;
} Dz1NetworkInfo;

DZ1_CPPLINK DZ1_DLLPORT Dz1NetworkInfo* Dz1NetworkInfo_new(Dz1Asn1OctetStr* ipAddress,
	u16_t servicePort,
	Dz1Asn1OctetStr* providerServiceContext, Dz1Error* err);
static __inline__ Dz1NetworkInfo* Dz1NetworkInfo_gen(Dz1Error* err) { return Dz1NetworkInfo_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1NetworkInfo* Dz1NetworkInfo_clone(Dz1NetworkInfo* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NetworkInfo_del(Dz1NetworkInfo* p);
static __inline__ void Dz1NetworkInfo_delAndSetNull(void* ptr)
{
	Dz1NetworkInfo** p = (Dz1NetworkInfo**)ptr;
	Dz1NetworkInfo_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1NetworkInfo_dump(Dz1NetworkInfo* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1NetworkInfo_fdump(FILE* fp, Dz1NetworkInfo* p, int tab);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NetworkInfo_fromASN(Dz1NetworkInfo* dst, NetworkInfo* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1NetworkInfo* Dz1NetworkInfo_newFromASN(NetworkInfo* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1NetworkInfo_toASN(NetworkInfo* dst, Dz1NetworkInfo* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT NetworkInfo* Dz1NetworkInfo_toNewASN(Dz1NetworkInfo* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1NetworkInfo
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommRxPDU
typedef struct Dz1CommRxPDU
{
	u32_t            psid;
	u8_t             channel;
	u8_t             rcpi;
	Dz1Asn1OctetStr* peerAddress;
	bool_t* sign;
	s64_t* payloadType;
	Dz1Asn1OctetStr* payload;
} Dz1CommRxPDU;

DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDU* Dz1CommRxPDU_new(u32_t psid,
	u8_t channel,
	u8_t rcpi,
	Dz1Asn1OctetStr* payload, Dz1Error* err);
static __inline__ Dz1CommRxPDU* Dz1CommRxPDU_gen(Dz1Error* err) { return Dz1CommRxPDU_new(0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDU* Dz1CommRxPDU_clone(Dz1CommRxPDU* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDU_del(Dz1CommRxPDU* p);
static __inline__ void Dz1CommRxPDU_delAndSetNull(void* ptr)
{
	Dz1CommRxPDU** p = (Dz1CommRxPDU**)ptr;
	Dz1CommRxPDU_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDU_dump(Dz1CommRxPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDU_fdump(FILE* fp, Dz1CommRxPDU* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommRxPDU_fromASN(Dz1CommRxPDU* dst, CommRxPDU* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDU* Dz1CommRxPDU_newFromASN(CommRxPDU* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommRxPDU_toASN(CommRxPDU* dst, Dz1CommRxPDU* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT CommRxPDU* Dz1CommRxPDU_toNewASN(Dz1CommRxPDU* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1CommRxPDU
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommRxPDURequest
typedef Dz1Asn1UTF8Str Dz1CommRxPDURequest;

#define Dz1CommRxPDURequest_clone             Dz1Asn1UTF8Str_clone
#define Dz1CommRxPDURequest_dump              Dz1Asn1UTF8Str_dump
#define Dz1CommRxPDURequest_fdump             Dz1Asn1UTF8Str_fdump

// Dz1CommRxPDURequest
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1CommRxPDUResponse
typedef struct Dz1CommRxPDUResponse
{
	void* storage;
	Dz1Error(*add)(struct Dz1CommRxPDUResponse* p, Dz1CommRxPDU* data);
	Dz1CommRxPDU** (*get_array)(struct Dz1CommRxPDUResponse* p, unsigned int* ret_cnt, Dz1Error* err);
	Dz1Error(*travel)(struct Dz1CommRxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommRxPDU* entry), void* ptr);
	Dz1Error(*travelForward)(struct Dz1CommRxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommRxPDU* entry), void* ptr);
	Dz1Error(*travelBackward)(struct Dz1CommRxPDUResponse* p, Dz1Error(*func)(void* ptr, Dz1CommRxPDU* entry), void* ptr);
	unsigned int (*count)(struct Dz1CommRxPDUResponse* p);
} Dz1CommRxPDUResponse;

DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_new(Dz1Error* err);
static __inline__ Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_gen(Dz1Error* err) { return Dz1CommRxPDUResponse_new(err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_clone(Dz1CommRxPDUResponse* src, Dz1Error* err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDUResponse_del(Dz1CommRxPDUResponse* p);
static __inline__ void Dz1CommRxPDUResponse_delAndSetNull(void* ptr)
{
	Dz1CommRxPDUResponse** p = (Dz1CommRxPDUResponse**)ptr;
	Dz1CommRxPDUResponse_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDUResponse_dump(Dz1CommRxPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT void Dz1CommRxPDUResponse_fdump(FILE* fp, Dz1CommRxPDUResponse* p, int tab);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommRxPDUResponse_fromASN(Dz1CommRxPDUResponse* dst, ASN1List* src);
DZ1_CPPLINK DZ1_DLLPORT Dz1CommRxPDUResponse* Dz1CommRxPDUResponse_newFromASN(ASN1List* src, Dz1Error* err);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1CommRxPDUResponse_toASN(ASN1List* dst, Dz1CommRxPDUResponse* src, ASN1WorkSpace* ws);
DZ1_CPPLINK DZ1_DLLPORT ASN1List* Dz1CommRxPDUResponse_toNewASN(Dz1CommRxPDUResponse* src, ASN1WorkSpace* ws, Dz1Error* err);
// Dz1CommRxPDUResponse
////////////////////////////////////////////////////////////////////////////////

#endif

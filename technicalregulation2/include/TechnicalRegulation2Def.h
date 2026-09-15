#ifndef _DZ1_TDC_TECHNICAL_REGULATION2_DEF_H_
#define _DZ1_TDC_TECHNICAL_REGULATION2_DEF_H_

////////////////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
////////////////////////////////////////////////////////////////////////////////

#include "libdz1_support.h"

////////////////////////////////////////////////////////////////////////////////
// NetworkInfoEntry
typedef struct NetworkInfoEntry
{
	Dz1Str		ipAddress;
	u16_t		servicePort;
	Dz1Str		provideServiceContext;
} NetworkInfoEntry;

DZ1_CPPLINK DZ1_DLLPORT NetworkInfoEntry *NetworkInfoEntry_new(Dz1Str ipAddress, 
															   u16_t servicePort, 
															   Dz1Str provideServiceContext, Dz1Error *err);
static __inline__ NetworkInfoEntry *NetworkInfoEntry_gen(Dz1Error *err) { return NetworkInfoEntry_new(NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t NetworkInfoEntry_copy(NetworkInfoEntry *dst, NetworkInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT NetworkInfoEntry *NetworkInfoEntry_clone(NetworkInfoEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoEntry_purge(NetworkInfoEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoEntry_del(NetworkInfoEntry *p);
static __inline__ void NetworkInfoEntry_delAndSetNull(void *ptr)
{
	NetworkInfoEntry **p = (NetworkInfoEntry **)ptr;
	if (p) { NetworkInfoEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoEntry_dump(NetworkInfoEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int NetworkInfoEntry_cmp(NetworkInfoEntry *a, NetworkInfoEntry *b); 
// NetworkInfoEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// NetworkInfoList
typedef struct NetworkInfoList
{
	void *storage;
	unsigned int (*count)(struct NetworkInfoList *p);
	Dz1Error (*travel)(struct NetworkInfoList *p, Dz1Error (*func)(void *ptr, NetworkInfoEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct NetworkInfoList *p, Dz1Error (*func)(void *ptr, NetworkInfoEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct NetworkInfoList *p, Dz1Error (*func)(void *ptr, NetworkInfoEntry *entry), void *ptr);
	NetworkInfoEntry **(*get_array)(struct NetworkInfoList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct NetworkInfoList *p, NetworkInfoEntry *data);
	bool_t (*remove)(struct NetworkInfoList *p, NetworkInfoEntry *key);
	NetworkInfoEntry *(*extract)(struct NetworkInfoList *p, NetworkInfoEntry *key);
	NetworkInfoEntry *(*find)(struct NetworkInfoList *p, NetworkInfoEntry *key);
	NetworkInfoEntry *(*getHead)(struct NetworkInfoList *p);
	int (*cmp)(NetworkInfoEntry *a, NetworkInfoEntry *b);
} NetworkInfoList;

DZ1_CPPLINK DZ1_DLLPORT NetworkInfoList *NetworkInfoList_new(Dz1Error *err);
static __inline__ NetworkInfoList *NetworkInfoList_gen(Dz1Error *err) { return NetworkInfoList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT NetworkInfoList *NetworkInfoList_clone(NetworkInfoList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoList_purge(NetworkInfoList *p);
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoList_del(NetworkInfoList *p);
static __inline__ void NetworkInfoList_delAndSetNull(void *ptr)
{
	NetworkInfoList **p = (NetworkInfoList **)ptr;
	if (p != NULL) { NetworkInfoList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void NetworkInfoList_dump(NetworkInfoList *p, int tab);

// NetworkInfoList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUEntry
typedef struct CommTxPDUEntry
{
	u32_t			 idx;
	u32_t			 psid;
	u8_t			 priority;
	u8_t			 channel;
	u16_t			 txInterval;
	Dz1Str			 ipAddress;
	u16_t			 servicePort;
	Dz1Str			 provideServiceContext;
	time_t			 deliveryStart;
	time_t			 deliveryStop;
	bool_t			 signature;
	s64_t			 payloadType;
	Dz1Binary		*payload;
	s8_t			 txPower;
	u8_t			 txDataRate;
	bool_t			 channelNumberHdrExt;
	bool_t			 dataRateHdrExt;
	bool_t			 txPowerHdrExt;
} CommTxPDUEntry;

DZ1_CPPLINK DZ1_DLLPORT CommTxPDUEntry *CommTxPDUEntry_new(u32_t idx, 
														   u32_t psid, 
														   u8_t priority, 
														   u8_t channel, 
														   u16_t txInterval, 
														   time_t deliveryStart, 
														   time_t deliveryStop, 
														   Dz1Binary *payload, Dz1Error *err);
static __inline__ CommTxPDUEntry *CommTxPDUEntry_gen(Dz1Error *err) { return CommTxPDUEntry_new(0, 0, 0, 0, 0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CommTxPDUEntry_copy(CommTxPDUEntry *dst, CommTxPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CommTxPDUEntry *CommTxPDUEntry_clone(CommTxPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUEntry_purge(CommTxPDUEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUEntry_del(CommTxPDUEntry *p);
static __inline__ void CommTxPDUEntry_delAndSetNull(void *ptr)
{
	CommTxPDUEntry **p = (CommTxPDUEntry **)ptr;
	if (p) { CommTxPDUEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUEntry_dump(CommTxPDUEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int CommTxPDUEntry_cmp(CommTxPDUEntry *a, CommTxPDUEntry *b); 
// CommTxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommTxPDUList
typedef struct CommTxPDUList
{
	void *storage;
	unsigned int (*count)(struct CommTxPDUList *p);
	Dz1Error (*travel)(struct CommTxPDUList *p, Dz1Error (*func)(void *ptr, CommTxPDUEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct CommTxPDUList *p, Dz1Error (*func)(void *ptr, CommTxPDUEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct CommTxPDUList *p, Dz1Error (*func)(void *ptr, CommTxPDUEntry *entry), void *ptr);
	CommTxPDUEntry **(*get_array)(struct CommTxPDUList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct CommTxPDUList *p, CommTxPDUEntry *data);
	bool_t (*remove)(struct CommTxPDUList *p, CommTxPDUEntry *key);
	CommTxPDUEntry *(*extract)(struct CommTxPDUList *p, CommTxPDUEntry *key);
	CommTxPDUEntry *(*find)(struct CommTxPDUList *p, CommTxPDUEntry *key);
	CommTxPDUEntry *(*getHead)(struct CommTxPDUList *p);
	int (*cmp)(CommTxPDUEntry *a, CommTxPDUEntry *b);
} CommTxPDUList;

DZ1_CPPLINK DZ1_DLLPORT CommTxPDUList *CommTxPDUList_new(Dz1Error *err);
static __inline__ CommTxPDUList *CommTxPDUList_gen(Dz1Error *err) { return CommTxPDUList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT CommTxPDUList *CommTxPDUList_clone(CommTxPDUList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUList_purge(CommTxPDUList *p);
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUList_del(CommTxPDUList *p);
static __inline__ void CommTxPDUList_delAndSetNull(void *ptr)
{
	CommTxPDUList **p = (CommTxPDUList **)ptr;
	if (p != NULL) { CommTxPDUList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CommTxPDUList_dump(CommTxPDUList *p, int tab);

// CommTxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUEntry
typedef struct CommRxPDUEntry
{
	u32_t			 psid;
	u8_t			 channel;
	u8_t			 rcpi;
	Dz1Str			 peerAddress;
	bool_t			 sign;
	s64_t			 payloadType;
	Dz1Binary		*payload;
} CommRxPDUEntry;

DZ1_CPPLINK DZ1_DLLPORT CommRxPDUEntry *CommRxPDUEntry_new(u32_t psid, 
														   u8_t channel, 
														   u8_t rcpi, 
														   Dz1Binary *payload, Dz1Error *err);
static __inline__ CommRxPDUEntry *CommRxPDUEntry_gen(Dz1Error *err) { return CommRxPDUEntry_new(0, 0, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t CommRxPDUEntry_copy(CommRxPDUEntry *dst, CommRxPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT CommRxPDUEntry *CommRxPDUEntry_clone(CommRxPDUEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUEntry_purge(CommRxPDUEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUEntry_del(CommRxPDUEntry *p);
static __inline__ void CommRxPDUEntry_delAndSetNull(void *ptr)
{
	CommRxPDUEntry **p = (CommRxPDUEntry **)ptr;
	if (p) { CommRxPDUEntry_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUEntry_dump(CommRxPDUEntry *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int CommRxPDUEntry_cmp(CommRxPDUEntry *a, CommRxPDUEntry *b); 
// CommRxPDUEntry
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// CommRxPDUList
typedef struct CommRxPDUList
{
	void *storage;
	unsigned int (*count)(struct CommRxPDUList *p);
	Dz1Error (*travel)(struct CommRxPDUList *p, Dz1Error (*func)(void *ptr, CommRxPDUEntry *entry), void *ptr);
	Dz1Error (*travelForward)(struct CommRxPDUList *p, Dz1Error (*func)(void *ptr, CommRxPDUEntry *entry), void *ptr);
	Dz1Error (*travelBackward)(struct CommRxPDUList *p, Dz1Error (*func)(void *ptr, CommRxPDUEntry *entry), void *ptr);
	CommRxPDUEntry **(*get_array)(struct CommRxPDUList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*add)(struct CommRxPDUList *p, CommRxPDUEntry *data);
	bool_t (*remove)(struct CommRxPDUList *p, CommRxPDUEntry *key);
	CommRxPDUEntry *(*extract)(struct CommRxPDUList *p, CommRxPDUEntry *key);
	CommRxPDUEntry *(*find)(struct CommRxPDUList *p, CommRxPDUEntry *key);
	CommRxPDUEntry *(*getHead)(struct CommRxPDUList *p);
	int (*cmp)(CommRxPDUEntry *a, CommRxPDUEntry *b);
} CommRxPDUList;

DZ1_CPPLINK DZ1_DLLPORT CommRxPDUList *CommRxPDUList_new(Dz1Error *err);
static __inline__ CommRxPDUList *CommRxPDUList_gen(Dz1Error *err) { return CommRxPDUList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT CommRxPDUList *CommRxPDUList_clone(CommRxPDUList *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUList_purge(CommRxPDUList *p);
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUList_del(CommRxPDUList *p);
static __inline__ void CommRxPDUList_delAndSetNull(void *ptr)
{
	CommRxPDUList **p = (CommRxPDUList **)ptr;
	if (p != NULL) { CommRxPDUList_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void CommRxPDUList_dump(CommRxPDUList *p, int tab);

// CommRxPDUList
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2_EamPresent
typedef enum TechnicalRegulation2_EamPresent
{
	TechnicalRegulation2_EamPresent_comm_tx_pdu,
	TechnicalRegulation2_EamPresent_comm_rx_pdu,
	TechnicalRegulation2_EamPresent_max
} TechnicalRegulation2_EamPresent;

DZ1_CPPLINK str_t TechnicalRegulation2_EamPresentStrA(TechnicalRegulation2_EamPresent v);
DZ1_CPPLINK TechnicalRegulation2_EamPresent TechnicalRegulation2_EamPresentFromStrA(str_t str);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK wstr_t TechnicalRegulation2_EamPresentStrW(TechnicalRegulation2_EamPresent v);
DZ1_CPPLINK TechnicalRegulation2_EamPresent TechnicalRegulation2_EamPresentFromStrW(wstr_t str);
#ifdef UNICODE
#define TechnicalRegulation2_EamPresentStr TechnicalRegulation2_EamPresentStrW
#define TechnicalRegulation2_EamPresentFromStr TechnicalRegulation2_EamPresentFromStrW
#else // UNICODE
#define TechnicalRegulation2_EamPresentStr TechnicalRegulation2_EamPresentStrA
#define TechnicalRegulation2_EamPresentFromStr TechnicalRegulation2_EamPresentFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define TechnicalRegulation2_EamPresentStr TechnicalRegulation2_EamPresentStrA
#define TechnicalRegulation2_EamPresentFromStr TechnicalRegulation2_EamPresentFromStrA
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2_EamPresent *TechnicalRegulation2_EamPresent_new(TechnicalRegulation2_EamPresent *src, Dz1Error *err);
static __inline__ TechnicalRegulation2_EamPresent *TechnicalRegulation2_EamPresent_gen(Dz1Error *err) { TechnicalRegulation2_EamPresent v = TechnicalRegulation2_EamPresent_max; return TechnicalRegulation2_EamPresent_new(&v, err); }
#define TechnicalRegulation2_EamPresent_clone             TechnicalRegulation2_EamPresent_new
static __inline__ void TechnicalRegulation2_EamPresent_del(TechnicalRegulation2_EamPresent *p) { if (p != NULL) Dz1Free(p); }
static __inline__ void TechnicalRegulation2_EamPresent_delAndSetNull(void *ptr)
{
	TechnicalRegulation2_EamPresent **p = (TechnicalRegulation2_EamPresent **)ptr;
	if (p != NULL) { TechnicalRegulation2_EamPresent_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2_EamPresent_dump(TechnicalRegulation2_EamPresent *v, int tab);
// TechnicalRegulation2_EamPresent
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// TechnicalRegulation2_Eam
typedef struct TechnicalRegulation2_Eam
{
	TechnicalRegulation2_EamPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		CommTxPDUList		*comm_tx_pdu;
		CommRxPDUList		*comm_rx_pdu;
	} x;
} TechnicalRegulation2_Eam;

DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2_Eam *TechnicalRegulation2_Eam_new(TechnicalRegulation2_EamPresent present, void *ptr, Dz1Error *err);
static __inline__ TechnicalRegulation2_Eam *TechnicalRegulation2_Eam_gen(Dz1Error *err) { return TechnicalRegulation2_Eam_new(TechnicalRegulation2_EamPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT bool_t  TechnicalRegulation2_Eam_copy(TechnicalRegulation2_Eam *dst, TechnicalRegulation2_Eam *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT TechnicalRegulation2_Eam *TechnicalRegulation2_Eam_clone(TechnicalRegulation2_Eam *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2_Eam_purge(TechnicalRegulation2_Eam *p);
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2_Eam_del(TechnicalRegulation2_Eam *p);
static __inline__ void TechnicalRegulation2_Eam_delAndSetNull(void *ptr)
{
	TechnicalRegulation2_Eam **p = (TechnicalRegulation2_Eam **)ptr;
	if (p != NULL) { TechnicalRegulation2_Eam_del(*p); *p = NULL; }
}
DZ1_CPPLINK DZ1_DLLPORT void TechnicalRegulation2_Eam_dump(TechnicalRegulation2_Eam *p, int tab);
// TechnicalRegulation2_Eam
////////////////////////////////////////////////////////////////////////////////

#endif

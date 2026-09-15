#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_MSG_DEF_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_MSG_DEF_H_

#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>

#include "libdz1_support.h"
#include "dz1_serial.h"


typedef struct Dz1TcpSerialMsgOpen
{
	s32_t             port;
	u32_t             baud;
	Dz1SerialParity   parity;
	Dz1SerialStopBit  stopBit;
	bool_t            fullDuplex;
	Dz1SerialRTSCTS   flowRTSCTS;
	Dz1SerialDSRDTR   flowDSRDTR;
	Dz1SerialXONXOFF  flowXONXOFF;
	bool_t            useRingInd;
	bool_t            useCtsChanged;
	bool_t            useDsrChanged;
} Dz1TcpSerialMsgOpen;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgOpen *Dz1TcpSerialMsgOpen_new(s32_t port, 
																	 u32_t baud, 
																	 Dz1SerialParity parity, 
																	 Dz1SerialStopBit stopBit, 
																	 bool_t fullDuplex, 
																	 Dz1SerialRTSCTS flowRTSCTS, 
																	 Dz1SerialDSRDTR flowDSRDTR, 
																	 Dz1SerialXONXOFF flowXONXOFF, 
																	 bool_t useRingInd, 
																	 bool_t useCtsChanged, 
																	 bool_t useDsrChanged, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgOpen *Dz1TcpSerialMsgOpen_gen(Dz1Error *err) { return Dz1TcpSerialMsgOpen_new(0, 0, Dz1SerialParity_max, Dz1SerialStopBit_max, 0, Dz1SerialRTSCTS_max, Dz1SerialDSRDTR_max, Dz1SerialXONXOFF_max, 0, 0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgOpen *Dz1TcpSerialMsgOpen_clone(Dz1TcpSerialMsgOpen *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgOpen_del(Dz1TcpSerialMsgOpen *p);
static __inline__ void Dz1TcpSerialMsgOpen_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsgOpen **p = (Dz1TcpSerialMsgOpen **)ptr;
	Dz1TcpSerialMsgOpen_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgOpen_dump(Dz1TcpSerialMsgOpen *p, int tab);

typedef struct Dz1TcpSerialMsgPin
{
	s32_t              port;
	Dz1SerialPinState  v;
} Dz1TcpSerialMsgPin;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgPin *Dz1TcpSerialMsgPin_new(s32_t port, Dz1SerialPinState v, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgPin *Dz1TcpSerialMsgPin_gen(Dz1Error *err) { return Dz1TcpSerialMsgPin_new(0, Dz1SerialPinState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgPin *Dz1TcpSerialMsgPin_clone(Dz1TcpSerialMsgPin *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgPin_del(Dz1TcpSerialMsgPin *p);
static __inline__ void Dz1TcpSerialMsgPin_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsgPin **p = (Dz1TcpSerialMsgPin **)ptr;
	Dz1TcpSerialMsgPin_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgPin_dump(Dz1TcpSerialMsgPin *p, int tab);

typedef struct Dz1TcpSerialMsgPinResult
{
	s32_t              port;
	Dz1SerialPinState  v;
	s32_t              status;
} Dz1TcpSerialMsgPinResult;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgPinResult *Dz1TcpSerialMsgPinResult_new(s32_t port, 
																			   Dz1SerialPinState v, 
																			   s32_t status, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgPinResult *Dz1TcpSerialMsgPinResult_gen(Dz1Error *err) { return Dz1TcpSerialMsgPinResult_new(0, Dz1SerialPinState_max, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgPinResult *Dz1TcpSerialMsgPinResult_clone(Dz1TcpSerialMsgPinResult *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgPinResult_del(Dz1TcpSerialMsgPinResult *p);
static __inline__ void Dz1TcpSerialMsgPinResult_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsgPinResult **p = (Dz1TcpSerialMsgPinResult **)ptr;
	Dz1TcpSerialMsgPinResult_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgPinResult_dump(Dz1TcpSerialMsgPinResult *p, int tab);

typedef struct Dz1TcpSerialMsgStream
{
	s32_t      port;
	Dz1Binary *stream;
} Dz1TcpSerialMsgStream;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgStream *Dz1TcpSerialMsgStream_new(s32_t port, Dz1Binary *stream, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgStream *Dz1TcpSerialMsgStream_gen(Dz1Error *err) { return Dz1TcpSerialMsgStream_new(0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgStream *Dz1TcpSerialMsgStream_clone(Dz1TcpSerialMsgStream *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgStream_del(Dz1TcpSerialMsgStream *p);
static __inline__ void Dz1TcpSerialMsgStream_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsgStream **p = (Dz1TcpSerialMsgStream **)ptr;
	Dz1TcpSerialMsgStream_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgStream_dump(Dz1TcpSerialMsgStream *p, int tab);

typedef struct Dz1TcpSerialMsgReply
{
	s32_t  port;
	s32_t  status;
} Dz1TcpSerialMsgReply;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgReply *Dz1TcpSerialMsgReply_new(s32_t port, s32_t status, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgReply *Dz1TcpSerialMsgReply_gen(Dz1Error *err) { return Dz1TcpSerialMsgReply_new(0, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgReply *Dz1TcpSerialMsgReply_clone(Dz1TcpSerialMsgReply *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgReply_del(Dz1TcpSerialMsgReply *p);
static __inline__ void Dz1TcpSerialMsgReply_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsgReply **p = (Dz1TcpSerialMsgReply **)ptr;
	Dz1TcpSerialMsgReply_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgReply_dump(Dz1TcpSerialMsgReply *p, int tab);


typedef enum Dz1TcpSerialMsgPresent
{
	Dz1TcpSerialMsgPresent_openPortReq,
	Dz1TcpSerialMsgPresent_openPortRsp,
	Dz1TcpSerialMsgPresent_closePortReq,
	Dz1TcpSerialMsgPresent_closePortRsp,
	Dz1TcpSerialMsgPresent_writePortReq,
	Dz1TcpSerialMsgPresent_writePortRsp,
	Dz1TcpSerialMsgPresent_writeDoneReq,
	Dz1TcpSerialMsgPresent_writeDoneRsp,
	Dz1TcpSerialMsgPresent_setRTSReq,
	Dz1TcpSerialMsgPresent_setRTSRsp,
	Dz1TcpSerialMsgPresent_getCTSReq,
	Dz1TcpSerialMsgPresent_getCTSRsp,
	Dz1TcpSerialMsgPresent_setDTRReq,
	Dz1TcpSerialMsgPresent_setDTRRsp,
	Dz1TcpSerialMsgPresent_getDSRReq,
	Dz1TcpSerialMsgPresent_getDSRRsp,
	Dz1TcpSerialMsgPresent_received,
	Dz1TcpSerialMsgPresent_ringIndicated,
	Dz1TcpSerialMsgPresent_ctsChanged,
	Dz1TcpSerialMsgPresent_dsrChanged,
	Dz1TcpSerialMsgPresent_max
} Dz1TcpSerialMsgPresent;

DZ1_CPPLINK str_t Dz1TcpSerialMsgPresentStrA(Dz1TcpSerialMsgPresent v);
DZ1_CPPLINK Dz1TcpSerialMsgPresent Dz1TcpSerialMsgPresentFromStrA(str_t str);

DZ1_CPPLINK wstr_t Dz1TcpSerialMsgPresentStrW(Dz1TcpSerialMsgPresent v);
DZ1_CPPLINK Dz1TcpSerialMsgPresent Dz1TcpSerialMsgPresentFromStrW(wstr_t str);

#ifdef UNICODE
#define Dz1TcpSerialMsgPresentStr Dz1TcpSerialMsgPresentStrW
#define Dz1TcpSerialMsgPresentFromStr Dz1TcpSerialMsgPresentFromStrW
#else // UNICODE
#define Dz1TcpSerialMsgPresentStr Dz1TcpSerialMsgPresentStrA
#define Dz1TcpSerialMsgPresentFromStr Dz1TcpSerialMsgPresentFromStrA
#endif // UNICODE
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsgPresent *Dz1TcpSerialMsgPresent_new(Dz1TcpSerialMsgPresent *src, Dz1Error *err);
static __inline__ Dz1TcpSerialMsgPresent *Dz1TcpSerialMsgPresent_gen(Dz1Error *err) { Dz1TcpSerialMsgPresent v = Dz1TcpSerialMsgPresent_max; return Dz1TcpSerialMsgPresent_new(&v, err); }
#define Dz1TcpSerialMsgPresent_clone             Dz1TcpSerialMsgPresent_new
#define Dz1TcpSerialMsgPresent_del               Dz1u32_del
#define Dz1TcpSerialMsgPresent_delAndSetNull     Dz1u32_delAndSetNull
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsgPresent_dump(Dz1TcpSerialMsgPresent *v, int tab);


typedef struct Dz1TcpSerialMsg
{
	Dz1TcpSerialMsgPresent present;
	union
	{
		void *__ptr__;
		unsigned char b1[1];
		unsigned char b2[2];
		unsigned char b4[4];
		Dz1TcpSerialMsgOpen *openPortReq;
		Dz1TcpSerialMsgReply *openPortRsp;
		s32_t closePortReq;
		Dz1TcpSerialMsgReply *closePortRsp;
		Dz1TcpSerialMsgStream *writePortReq;
		Dz1TcpSerialMsgReply *writePortRsp;
		s32_t writeDoneReq;
		Dz1TcpSerialMsgReply *writeDoneRsp;
		Dz1TcpSerialMsgPin *setRTSReq;
		Dz1TcpSerialMsgReply *setRTSRsp;
		s32_t getCTSReq;
		Dz1TcpSerialMsgPinResult *getCTSRsp;
		Dz1TcpSerialMsgPin *setDTRReq;
		Dz1TcpSerialMsgReply *setDTRRsp;
		s32_t getDSRReq;
		Dz1TcpSerialMsgPinResult *getDSRRsp;
		Dz1TcpSerialMsgStream *received;
		Dz1TcpSerialMsgPin *ringIndicated;
		Dz1TcpSerialMsgPin *ctsChanged;
		Dz1TcpSerialMsgPin *dsrChanged;
	} x;
} Dz1TcpSerialMsg;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsg *Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent present, void *ptr, Dz1Error *err);
static __inline__ Dz1TcpSerialMsg *Dz1TcpSerialMsg_gen(Dz1Error *err) { return Dz1TcpSerialMsg_new(Dz1TcpSerialMsgPresent_max, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsg *Dz1TcpSerialMsg_clone(Dz1TcpSerialMsg *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsg_del(Dz1TcpSerialMsg *p);
static __inline__ void Dz1TcpSerialMsg_delAndSetNull(void *ptr)
{
	Dz1TcpSerialMsg **p = (Dz1TcpSerialMsg **)ptr;
	Dz1TcpSerialMsg_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialMsg_dump(Dz1TcpSerialMsg *p, int tab);
#endif

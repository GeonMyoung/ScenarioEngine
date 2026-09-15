#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_MSGS_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_MSGS_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientDef.h"


typedef struct Dz1TcpSerialClientMsgDefault
{
	u32_t *dummy;
} Dz1TcpSerialClientMsgDefault;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgDefault *Dz1TcpSerialClientMsgDefault_new(u32_t *dummy, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgDefault *Dz1TcpSerialClientMsgDefault_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgDefault_new(NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgDefault_del(Dz1TcpSerialClientMsgDefault *p);
static __inline__ void Dz1TcpSerialClientMsgDefault_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgDefault **p = (Dz1TcpSerialClientMsgDefault **)ptr;
	Dz1TcpSerialClientMsgDefault_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgDefault_dump(Dz1TcpSerialClientMsgDefault *p, int tab);

typedef struct Dz1TcpSerialClientMsgOpen
{
	s32_t                 portNum;
	u32_t                 baud;
	s32_t                 bitPerByte;
	Dz1SerialParity       parity;
	Dz1SerialStopBit      stopBit;
	bool_t                fullDuplex;
	Dz1SerialRTSCTS       flowRTSCTS;
	Dz1SerialDSRDTR       flowDSRDTR;
	Dz1SerialXONXOFF      flowXONXOFF;
	Dz1SerialByteConsume  byteConsume;
	void                 *byteConsumeParam;
	Dz1SerialPinChanged   ringInd;
	void                 *ringIndParam;
	Dz1SerialPinChanged   ctsChanged;
	void                 *ctsChangedParam;
	Dz1SerialPinChanged   dsrChanged;
	void                 *dsrChangedParam;
	Dz1SerialException    exception;
	void                 *exceptionParam;
	void                 *ret;
} Dz1TcpSerialClientMsgOpen;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgOpen *Dz1TcpSerialClientMsgOpen_new(s32_t portNum, 
																				 u32_t baud, 
																				 s32_t bitPerByte, 
																				 Dz1SerialParity parity, 
																				 Dz1SerialStopBit stopBit, 
																				 bool_t fullDuplex, 
																				 Dz1SerialRTSCTS flowRTSCTS, 
																				 Dz1SerialDSRDTR flowDSRDTR, 
																				 Dz1SerialXONXOFF flowXONXOFF, 
																				 Dz1SerialByteConsume byteConsume, 
																				 void *byteConsumeParam, 
																				 Dz1SerialPinChanged ringInd, 
																				 void *ringIndParam, 
																				 Dz1SerialPinChanged ctsChanged, 
																				 void *ctsChangedParam, 
																				 Dz1SerialPinChanged dsrChanged, 
																				 void *dsrChangedParam, 
																				 Dz1SerialException exception, 
																				 void *exceptionParam, 
																				 void *ret, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgOpen *Dz1TcpSerialClientMsgOpen_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgOpen_new(0, 0, 0, Dz1SerialParity_max, Dz1SerialStopBit_max, 0, Dz1SerialRTSCTS_max, Dz1SerialDSRDTR_max, Dz1SerialXONXOFF_max, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgOpen_del(Dz1TcpSerialClientMsgOpen *p);
static __inline__ void Dz1TcpSerialClientMsgOpen_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgOpen **p = (Dz1TcpSerialClientMsgOpen **)ptr;
	Dz1TcpSerialClientMsgOpen_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgOpen_dump(Dz1TcpSerialClientMsgOpen *p, int tab);

typedef struct Dz1TcpSerialClientMsgPort
{
	s32_t  portNum;
} Dz1TcpSerialClientMsgPort;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgPort *Dz1TcpSerialClientMsgPort_new(s32_t portNum, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgPort *Dz1TcpSerialClientMsgPort_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgPort_new(0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgPort_del(Dz1TcpSerialClientMsgPort *p);
static __inline__ void Dz1TcpSerialClientMsgPort_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgPort **p = (Dz1TcpSerialClientMsgPort **)ptr;
	Dz1TcpSerialClientMsgPort_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgPort_dump(Dz1TcpSerialClientMsgPort *p, int tab);

typedef struct Dz1TcpSerialClientMsgPin
{
	s32_t              portNum;
	Dz1SerialPinState  pin;
} Dz1TcpSerialClientMsgPin;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgPin *Dz1TcpSerialClientMsgPin_new(s32_t portNum, Dz1SerialPinState pin, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgPin *Dz1TcpSerialClientMsgPin_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgPin_new(0, Dz1SerialPinState_max, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgPin_del(Dz1TcpSerialClientMsgPin *p);
static __inline__ void Dz1TcpSerialClientMsgPin_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgPin **p = (Dz1TcpSerialClientMsgPin **)ptr;
	Dz1TcpSerialClientMsgPin_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgPin_dump(Dz1TcpSerialClientMsgPin *p, int tab);

typedef struct Dz1TcpSerialClientMsgChunk
{
	s32_t      portNum;
	Dz1Binary *stream;
	ssize_t    ret;
} Dz1TcpSerialClientMsgChunk;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgChunk *Dz1TcpSerialClientMsgChunk_new(s32_t portNum, 
																				   Dz1Binary *stream, 
																				   ssize_t ret, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgChunk *Dz1TcpSerialClientMsgChunk_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgChunk_new(0, NULL, 0, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgChunk_del(Dz1TcpSerialClientMsgChunk *p);
static __inline__ void Dz1TcpSerialClientMsgChunk_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgChunk **p = (Dz1TcpSerialClientMsgChunk **)ptr;
	Dz1TcpSerialClientMsgChunk_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgChunk_dump(Dz1TcpSerialClientMsgChunk *p, int tab);

typedef struct Dz1TcpSerialClientMsgSetByteConsume
{
	s32_t                 portNum;
	Dz1SerialByteConsume  byteConsume;
	void                 *byteConsumeParam;
} Dz1TcpSerialClientMsgSetByteConsume;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgSetByteConsume *Dz1TcpSerialClientMsgSetByteConsume_new(s32_t portNum, 
																									 Dz1SerialByteConsume byteConsume, 
																									 void *byteConsumeParam, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgSetByteConsume *Dz1TcpSerialClientMsgSetByteConsume_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgSetByteConsume_new(0, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgSetByteConsume_del(Dz1TcpSerialClientMsgSetByteConsume *p);
static __inline__ void Dz1TcpSerialClientMsgSetByteConsume_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgSetByteConsume **p = (Dz1TcpSerialClientMsgSetByteConsume **)ptr;
	Dz1TcpSerialClientMsgSetByteConsume_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgSetByteConsume_dump(Dz1TcpSerialClientMsgSetByteConsume *p, int tab);

typedef struct Dz1TcpSerialClientMsgReceived
{
	Dz1SockAddr *peer;
	Dz1SockAddr *local;
	Dz1Binary   *stream;
} Dz1TcpSerialClientMsgReceived;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientMsgReceived *Dz1TcpSerialClientMsgReceived_new(Dz1SockAddr *peer, 
																						 Dz1SockAddr *local, 
																						 Dz1Binary *stream, Dz1Error *err);
static __inline__ Dz1TcpSerialClientMsgReceived *Dz1TcpSerialClientMsgReceived_gen(Dz1Error *err) { return Dz1TcpSerialClientMsgReceived_new(NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgReceived_del(Dz1TcpSerialClientMsgReceived *p);
static __inline__ void Dz1TcpSerialClientMsgReceived_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientMsgReceived **p = (Dz1TcpSerialClientMsgReceived **)ptr;
	Dz1TcpSerialClientMsgReceived_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientMsgReceived_dump(Dz1TcpSerialClientMsgReceived *p, int tab);

#endif

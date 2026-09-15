#ifndef _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_ENV_H_
#define _DZ1_TDC_DZ1_TCP_SERIAL_CLIENT_ENV_H_

//////////////////////////////////////////////////////////////////////
#include <dz1_error.h>
#include <dz1_int.h>
#include <dz1_real.h>
#include <dz1_str.h>
#include <dz1_sock_addr.h>
//////////////////////////////////////////////////////////////////////

#include "Dz1TcpSerialClientDef.h"


typedef struct Dz1TcpSerialClientPort
{
	s32_t                 port;
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
	void                 *req_sg;
} Dz1TcpSerialClientPort;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientPort *Dz1TcpSerialClientPort_new(s32_t port, 
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
																		   void *req_sg, Dz1Error *err);
static __inline__ Dz1TcpSerialClientPort *Dz1TcpSerialClientPort_gen(Dz1Error *err) { return Dz1TcpSerialClientPort_new(0, 0, 0, Dz1SerialParity_max, Dz1SerialStopBit_max, 0, Dz1SerialRTSCTS_max, Dz1SerialDSRDTR_max, Dz1SerialXONXOFF_max, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientPort_del(Dz1TcpSerialClientPort *p);
static __inline__ void Dz1TcpSerialClientPort_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientPort **p = (Dz1TcpSerialClientPort **)ptr;
	Dz1TcpSerialClientPort_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientPort_dump(Dz1TcpSerialClientPort *p, int tab);
DZ1_CPPLINK DZ1_DLLPORT int Dz1TcpSerialClientPort_cmp(Dz1TcpSerialClientPort *a, Dz1TcpSerialClientPort *b);


typedef struct Dz1TcpSerialClientPortList
{
	void *storage;
	Dz1Error (*add)(struct Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *data);
	void (*remove)(struct Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key);
	Dz1TcpSerialClientPort *(*extract)(struct Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key);
	Dz1TcpSerialClientPort **(*get_array)(struct Dz1TcpSerialClientPortList *p, unsigned int *ret_cnt, Dz1Error *err);
	Dz1Error (*travel)(struct Dz1TcpSerialClientPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialClientPort *entry), void *ptr);
	Dz1Error (*travelForward)(struct Dz1TcpSerialClientPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialClientPort *entry), void *ptr);
	Dz1Error (*travelBackward)(struct Dz1TcpSerialClientPortList *p, Dz1Error (*func)(void *ptr, Dz1TcpSerialClientPort *entry), void *ptr);
	Dz1TcpSerialClientPort *(*find)(struct Dz1TcpSerialClientPortList *p, Dz1TcpSerialClientPort *key);
	int (*cmp)(Dz1TcpSerialClientPort *a, Dz1TcpSerialClientPort *b);
	unsigned int (*count)(struct Dz1TcpSerialClientPortList *p);
} Dz1TcpSerialClientPortList;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientPortList *Dz1TcpSerialClientPortList_new(Dz1Error *err);
static __inline__ Dz1TcpSerialClientPortList *Dz1TcpSerialClientPortList_gen(Dz1Error *err) { return Dz1TcpSerialClientPortList_new(err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientPortList_del(Dz1TcpSerialClientPortList *p);
static __inline__ void Dz1TcpSerialClientPortList_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientPortList **p = (Dz1TcpSerialClientPortList **)ptr;
	Dz1TcpSerialClientPortList_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientPortList_dump(Dz1TcpSerialClientPortList *p, int tab);


typedef struct Dz1TcpSerialClientEnv
{
	void                       *tSelf;
	Dz1TcpClientSocket         *sock;
	u32_t                       rcvr;
	Dz1SocketBuf               *rxBuf;
	Dz1TcpSerialClientPortList *ports;
} Dz1TcpSerialClientEnv;

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialClientEnv *Dz1TcpSerialClientEnv_new(void *tSelf, 
																		 Dz1TcpClientSocket *sock, 
																		 u32_t rcvr, 
																		 Dz1SocketBuf *rxBuf, Dz1Error *err);
static __inline__ Dz1TcpSerialClientEnv *Dz1TcpSerialClientEnv_gen(Dz1Error *err) { return Dz1TcpSerialClientEnv_new(NULL, NULL, 0, NULL, err); }
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientEnv_del(Dz1TcpSerialClientEnv *p);
static __inline__ void Dz1TcpSerialClientEnv_delAndSetNull(void *ptr)
{
	Dz1TcpSerialClientEnv **p = (Dz1TcpSerialClientEnv **)ptr;
	Dz1TcpSerialClientEnv_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void Dz1TcpSerialClientEnv_dump(Dz1TcpSerialClientEnv *p, int tab);

#endif

#ifndef DZ1_TCP_SERIAL_CLIENT_H
#define DZ1_TCP_SERIAL_CLIENT_H

#include <dz1_serial.h>
#include <Dz1TcpSerialClientDef.h>

DZ1_CPPLINK void *Dz1TcpSerialClient_new(Dz1SockAddr *serverAddr,
										 Dz1TcpSerialClientException exceptionProc,
										 void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Dz1TcpSerialClient_del(void *task);

DZ1_CPPLINK void				*Dz1TcpSerialClient_open(void					*task,
														 int					 portNum,
														 u32_t					 baud,
														 int					 bitPerByte,
														 Dz1SerialParity		 parity,
														 Dz1SerialStopBit		 stopBit,
														 bool_t					 fullDuplex,

														 Dz1SerialRTSCTS		 flowRTSCTS,
														 Dz1SerialDSRDTR		 flowDSRDTR,
														 Dz1SerialXONXOFF		 flowXONXOFF,

														 Dz1SerialByteConsume	 byteConsume,	void *byteConsumeParam,
														 Dz1SerialPinChanged	 ringInd,		void *ringIndParam,
														 Dz1SerialPinChanged	 ctsChanged,	void *ctsChangedParam,
														 Dz1SerialPinChanged	 dsrChanged,	void *dsrChangedParam,	
														 Dz1SerialException		 exception,		void *exceptionParam,

														 Dz1Error *err);

DZ1_CPPLINK void				*Dz1TcpSerialClient_openNullModem(void					*task,
																  int					 portNum,
																  u32_t					 baud,
																  int					 bitPerByte,
																  Dz1SerialParity		 pairty,
																  Dz1SerialStopBit		 stopBit,
																  bool_t				 duplex,
																  Dz1SerialXONXOFF		 xonoffFlowControl,
																  Dz1SerialByteConsume	 byteConsume, void *byteConsumeParam,
																  Dz1SerialException	 exception, void *exceptionParam,
																  Dz1Error *err);

DZ1_CPPLINK Dz1Error			 Dz1TcpSerialClient_close(void *task, void *p);
typedef struct Dz1TcpSerialClientCloseAndSetNullArg
{
	void *task;
	void **p;
} Dz1TcpSerialClientCloseAndSetNullArg;

static __inline__ void			 Dz1TcpSerialClient_closeAndSetNull(void *ptr)
{
	Dz1TcpSerialClientCloseAndSetNullArg *arg = (Dz1TcpSerialClientCloseAndSetNullArg *)ptr;
	Dz1TcpSerialClient_close(arg->task, *(arg->p)); *(arg->p) = NULL;
}

DZ1_CPPLINK Dz1Error			 Dz1TcpSerialClient_setRTS(void *task, void *ptr, Dz1SerialPinState state);
DZ1_CPPLINK Dz1Error			 Dz1TcpSerialClient_setDTR(void *task, void *ptr, Dz1SerialPinState state);

DZ1_CPPLINK Dz1SerialPinState	 Dz1TcpSerialClient_getDSR(void *task, void *ptr, Dz1Error *errp);
DZ1_CPPLINK Dz1SerialPinState	 Dz1TcpSerialClient_getCTS(void *task, void *ptr, Dz1Error *errp);

DZ1_CPPLINK ssize_t				 Dz1TcpSerialClient_write(void *task, void *p, const unsigned char *buf, size_t size, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1TcpSerialClient_waitWriteDone(void *task, void *ptr);

DZ1_CPPLINK Dz1Error			 Dz1TcpSerialClient_setByteConsume(void *task, void *ptr,
																   Dz1SerialByteConsume byteConsume,
																   void *byteConsumeParam);

#endif

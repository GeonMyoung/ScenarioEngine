#ifndef DZ1_TCP_SERIAL_CLIENT_H_LOCAL
#define DZ1_TCP_SERIAL_CLIENT_H_LOCAL

#include <Dz1TcpSerialClient.h>

DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_open(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_close(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_setRTS(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_setDTR(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_getDSR(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_getCTS(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_write(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_writeDone(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_setByteConsume(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);

DZ1_CPPLINK u32_t Dz1TcpSerialClientReceiver_start(Dz1SockAddr *peer, Dz1SockAddr *local, Dz1TcpClientSocket *sock, u32_t dstQueueID, Dz1Error *err);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_disconnected(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *err);
DZ1_CPPLINK Dz1TaskProcStatus Dz1TcpSerialClient_m_recv(void *uArg, void *uRsc, void *timer, Dz1TaskSigMsg **sg, Dz1Error *errp);

#endif
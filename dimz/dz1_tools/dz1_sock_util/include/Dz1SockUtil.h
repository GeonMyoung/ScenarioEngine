#ifndef DZ1_SOCK_UTIL_H
#define DZ1_SOCK_UTIL_H

#include <dz1_task.h>
#include <dz1_socket_acceptor.h>
#include <Dz1SockUtilDef.h>

#define DZ1_SOCK_UTIL_ACCEPTOR_MSG					0xFF100000

#define DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED			(DZ1_SOCK_UTIL_ACCEPTOR_MSG | 0x00000001)
#define DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION			(DZ1_SOCK_UTIL_ACCEPTOR_MSG | 0x000000FF)


#define DZ1_SOCK_UTIL_RECEIVER_MSG					0xFF200000

#define DZ1_SOCK_UTIL_RECEIVER_RECEIVED				(DZ1_SOCK_UTIL_RECEIVER_MSG | 0x00000001)
#define DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED			(DZ1_SOCK_UTIL_RECEIVER_MSG | 0x000000F1)

#define DZ1_SOCK_UTIL_RECEIVER2_RECEIVED			(DZ1_SOCK_UTIL_RECEIVER_MSG | 0x00000002)
#define DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED		(DZ1_SOCK_UTIL_RECEIVER_MSG | 0x000000F2)


#define DZ1_SOCK_UTIL_TRANSMITER_MSG				0xFF300000

#define DZ1_SOCK_UTIL_TRANSMITER_SENT				(DZ1_SOCK_UTIL_TRANSMITER_MSG | 0x00000001)
#define DZ1_SOCK_UTIL_TRANSMITER2_SENT				(DZ1_SOCK_UTIL_TRANSMITER_MSG | 0x00000002)

#define DZ1_SOCK_UTIL_CONNECTOR_MSG					0xFF400000
#define DZ1_SOCK_UTIL_CONNECTOR_RESULT				(DZ1_SOCK_UTIL_CONNECTOR_MSG | 0x00000001)

///////////////////////////////////////////////////////////////////////////////
// TCP Server Socket Acceptor for TASK that
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_ACCEPTOR_CONNECTED(Dz1SockUtilAcceptorConnected)
// DZ1_SOCK_UTIL_ACCEPTOR_EXCEPTION(Dz1SockUtilAcceptorException)
// ----------------------------------------------------------------------------
DZ1_CPPLINK u32_t Dz1SockUtilAcceptorForTask_start(u32_t acceptorID, Dz1SockAddr *listenAddr,
												   u32_t parentTaskQueueID, Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Native TCP Socket Receiver for TASK that
// Socket Recognized by Socket Address
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER_RECEIVED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED(Dz1SockUtilReceiverReceived)
// ----------------------------------------------------------------------------
DZ1_CPPLINK u32_t Dz1SockUtilTcpReceiverForTask_start(Dz1TcpClientSocket **sock, bool_t autoClose,
													  Dz1SockAddr *peer, Dz1SockAddr *local,
													  size_t bufSize, u32_t parentTaskQueueID,
													  Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Native TCP Socket Receiver for TASK that
// Socket Recognized by Session ID
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED(Dz1SockUtilReceiver2Received)
// ----------------------------------------------------------------------------
DZ1_CPPLINK u32_t Dz1SockUtilTcpReceiver2ForTask_start(u32_t sessionID,  bool_t autoClose,
													   Dz1TcpClientSocket **sock,
													   Dz1SockAddr *peer, Dz1SockAddr *local,
													   size_t bufSize, u32_t parentTaskQueueID,
													   Dz1Error *err);

///////////////////////////////////////////////////////////////////////////////
// Callback Mode TCP Socket for TASK that
// Socket Recognized by Socket Address
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER_RECEIVED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_TRANSMITER_SENT(Dz1SockUtilTransmiterSent)
// ----------------------------------------------------------------------------
DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_modeCallback(Dz1TcpClientSocket *sock,
													   Dz1SockAddr *peer, Dz1SockAddr *local,
													   size_t rx_buf_size, u32_t parentTaskQueueID);

///////////////////////////////////////////////////////////////////////////////
// Callback Mode TCP Socket Receiver for TASK that
// Socket Recognized by Session ID
// Calling TASK will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_TRANSMITER2_SENT(Dz1SockUtilTransmiter2Sent)
// ----------------------------------------------------------------------------
DZ1_CPPLINK Dz1Error Dz1SockUtilTcpClient_mode2Callback(u32_t sessionID,
														Dz1TcpClientSocket *sock, 
														Dz1SockAddr *peer, Dz1SockAddr *local,
														size_t rx_buf_size, u32_t parentTaskQueueID);

///////////////////////////////////////////////////////////////////////////////
// Bulk Connector for TASK that
// Socket Connect to max concurrency
// Calling TASK what Dz1SockUtilBulkConnector_request function
// will received followed Message Type
// ----------------------------------------------------------------------------
// DZ1_SOCK_UTIL_CONNECTOR_RESULT(Dz1SockUtilBulkConnectResult)
// ----------------------------------------------------------------------------
typedef void Dz1SockUtilBulkConnector;
DZ1_CPPLINK Dz1SockUtilBulkConnector	*Dz1SockUtilBulkConnector_new(u8_t maxConcurrency, Dz1Error *err);
DZ1_CPPLINK void						 Dz1SockUtilBulkConnector_del(Dz1SockUtilBulkConnector *ptr);
static __inline__ void					 Dz1SockUtilBulkConnector_delAndSetNull(void *ptr)
{
	Dz1SockUtilBulkConnector **p = (Dz1SockUtilBulkConnector **)ptr;
	Dz1SockUtilBulkConnector_del(*p); *p = NULL;
}
DZ1_CPPLINK void						 Dz1SockUtilBulkConnector_dump(Dz1SockUtilBulkConnector *p, int tab);

// Register connecting request to Dz1SockUtilBulkConnector
DZ1_CPPLINK Dz1Error					 Dz1SockUtilBulkConnector_request(Dz1SockUtilBulkConnector *p, u32_t myQueueID, Dz1SockAddr *peer,
																		  u32_t period, bool_t wait_and_connect,
																		  void **userData, Dz1DelFunc userDataDel);

DZ1_CPPLINK void						 Dz1SockUtilBulkConnector_cancel(Dz1SockUtilBulkConnector *p, Dz1SockAddr *peer, u32_t myQueueID);

// when TASK received DZ1_SOCK_UTIL_CONNECTOR_RESULT message call this function
DZ1_CPPLINK Dz1SockUtilBulkConnectResult*Dz1SockUtilBulkConnector_msgProc(Dz1SockUtilBulkConnector *p, u32_t myQueueID, Dz1TaskSigMsg *sg, Dz1Error *err);
// Bulk Connector for TASK
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Dz1SockUtilTxFifo for TASK
// send data
DZ1_CPPLINK bool_t Dz1SockUtilTxFifo_isEmpty(Dz1SockUtilTxFifo *p);
DZ1_CPPLINK bool_t Dz1SockUtilTxFifo_send(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, u8_t *data, size_t sz, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1SockUtilTxFifo_send2(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, Dz1Binary **_bin, Dz1Error *err);

// when received *_SENT message
#define			   Dz1SockUtilTxFifo_sentProc(fifop, sockp, ep)		_Dz1SockUtilTxFifo_sentProc(fifop, sockp, NULL, ep)
DZ1_CPPLINK bool_t _Dz1SockUtilTxFifo_sentProc(Dz1SockUtilTxFifo *p, Dz1TcpClientSocket *sock, u32_t *ret_sz, Dz1Error *err);
// Dz1SockUtilTxFifo for TASK
///////////////////////////////////////////////////////////////////////////////

DZ1_CPPLINK Dz1CallbackSockIO *Dz1CallbackSockIO_new(Dz1SockAddr *peer, u32_t rx_buf_sz, Dz1Error *err);
DZ1_CPPLINK Dz1CallbackSockIO *Dz1CallbackSockIO_wrap(Dz1SockAddr **peer, Dz1SockAddr **local, u32_t rx_buf_sz, Dz1Error *err);

// DZ1_SOCK_UTIL_RECEIVER_RECEIVED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_RECEIVER_DISCONNECTED(Dz1SockUtilReceiverReceived)
// DZ1_SOCK_UTIL_TRANSMITER_SENT(Dz1SockUtilTransmiterSent)
DZ1_CPPLINK Dz1TcpClientSocket *Dz1CallbackSockIO_prepareMode1(Dz1CallbackSockIO *io, u32_t my_queue_id, Dz1TimeVal *conn_to, Dz1Error *err);

// DZ1_SOCK_UTIL_RECEIVER2_RECEIVED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_RECEIVER2_DISCONNECTED(Dz1SockUtilReceiver2Received)
// DZ1_SOCK_UTIL_TRANSMITER2_SENT(Dz1SockUtilTransmiter2Sent)
DZ1_CPPLINK Dz1TcpClientSocket *Dz1CallbackSockIO_prepareMode2(Dz1CallbackSockIO *io, u32_t my_queue_id, u16_t sid, Dz1Error *err);

#endif

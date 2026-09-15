#ifndef DZ1_TCP_CALLBACK_MSG_CODEC_H
#define DZ1_TCP_CALLBACK_MSG_CODEC_H

#include <Dz1TcpCallbackMsgDef.h>

DZ1_CPPLINK Dz1TcpCallbackMsg *Dz1TcpCallbackMsg_gen(Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1TcpCallbackMsg_enc(u8_t *dst, size_t size, Dz1TcpCallbackMsg *src, void *param, Dz1Error *err);
DZ1_CPPLINK ssize_t Dz1TcpCallbackMsg_dec(Dz1TcpCallbackMsg *dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
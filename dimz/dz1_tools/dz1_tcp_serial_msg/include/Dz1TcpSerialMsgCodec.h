#ifndef DZ1_TCP_SERIAL_MSG_CODEC_H
#define DZ1_TCP_SERIAL_MSG_CODEC_H

#include <Dz1TcpSerialMsgDef.h>

DZ1_CPPLINK DZ1_DLLPORT Dz1TcpSerialMsg *Dz1TcpSerialMsg_gen(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1TcpSerialMsg_enc(u8_t *dst, size_t size, Dz1TcpSerialMsg *src, void *param, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1TcpSerialMsg_dec(Dz1TcpSerialMsg *dst, u8_t *src, size_t size, void *param, Dz1Error *err);

#endif
#ifndef DZ1_TCP_SOCKET_SERVER_TASK_H
#define DZ1_TCP_SOCKET_SERVER_TASK_H

#include <dz1_error.h>
#include <dz1_task.h>
DZ1_CPPLINK void *Dz1TcpSocketServerTask_new(Dz1Error *err);

DZ1_CPPLINK Dz1Error Dz1TcpSocketServerTask_open(void *task, u16_t port);
DZ1_CPPLINK Dz1Error Dz1TcpSocketServerTask_open2(void *task, u16_t port);
DZ1_CPPLINK Dz1Error Dz1TcpSocketServerTask_open3(void *task, u16_t port);

DZ1_CPPLINK Dz1Error Dz1TcpSocketServerTask_close(void *task, u16_t port);

DZ1_CPPLINK Dz1Error Dz1TcpSocketServerTask_status(void *task);
#endif
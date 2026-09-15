#ifndef DZ1_INET_FTP_MESSAGE_H_LOCAL
#define DZ1_INET_FTP_MESSAGE_H_LOCAL

#include <dz1_task.h>

//DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_message(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_trasferDone(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_trasferFail(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
//DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_trasferTimeout(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_extendTimeout(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtp_disconnected(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);

#endif


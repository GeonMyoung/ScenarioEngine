#ifndef DZ1_INET_FTP_FSM_H_LOCAL
#define DZ1_INET_FTP_FSM_H_LOCAL

#include "dz1_inet_ftp_env.h"
#include "dz1_inet_ftp_fsm_def.h"

DZ1_CPPLINK Dz1Fsm2 *Dz1InetFtpFsm_new(Dz1InetFtpSession *session, Dz1Error *err);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtpFsm_replyMsgProc(void *uArg, void *uRsc, void *timer, void **sg, Dz1Error *errp);
DZ1_CPPLINK Dz1TaskProcStatus Dz1InetFtpFsm_replyMsgProc2(Dz1InetFtpSession *session,
														  void *uArg, void *uRsc, void *timer,
														  Dz1InetFtpEvent event, void **sg, Dz1Error *errp);

#endif


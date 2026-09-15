#ifndef DZ1_INET_FTP_H
#define DZ1_INET_FTP_H

#include <dz1_inet_ftp_def.h>

DZ1_CPPLINK void *Dz1InetFtp_new(str_t localCharSetName,
								 Dz1InetFtpException exceptionFunc,
								 void *exceptionArg, Dz1Error *err);


DZ1_CPPLINK Dz1Error Dz1InetFtpCall_transfer(void *tFTP, Dz1SockAddr *peer,
											 str_t user, str_t pass, str_t account, bool_t isPassive,
											 Dz1InetFtpTransferList *files,
											 Dz1InetFtpFileDoneInform cb, void *cbParam,
											 Dz1InetFtpTransferList **ret);

DZ1_CPPLINK Dz1Error Dz1InetFtpPost_transfer(void *tFTP, Dz1SockAddr *peer, str_t user, str_t pass, str_t account, bool_t isPassive,
											 Dz1InetFtpTransferList *files, Dz1InetFtpFileDoneInform cb, void *cbParam,
											 Dz1InetFtpMsgTransferDoneInform doneInform, void *doneInformParam);

#endif


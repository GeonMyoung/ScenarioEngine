#ifndef DZ1_INET_FTP_ENV_UTIL_H
#define DZ1_INET_FTP_ENV_UTIL_H

#include "dz1_inet_ftp_env.h"

DZ1_CPPLINK void Dz1InetFtpEnv_cleanup(Dz1InetFtpEnv *p);

DZ1_CPPLINK void Dz1InetFtpSession_cleanupRunTime(void *ptr);

typedef struct Dz1InetFtpSessionCleanupRuntimeArg
{
	Dz1InetFtpSession *session;
	void *timer;
} Dz1InetFtpSessionCleanupRuntimeArg;

DZ1_CPPLINK Dz1Error Dz1InetFtpTransferJobs_build(Dz1InetFtpSession *dst, Dz1InetFtpTransferList *files);

#endif


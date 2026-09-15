#ifndef DZ1_DAEMON_H
#define DZ1_DAEMON_H

#include <dz1_error.h>
#include <dz1_str.h>

#ifdef UNIX_SYSTEM
#else
// M$ Windows Service Control
DZ1_CPPLINK bool_t Dz1DaemonServiceCreate(Dz1Str serviceName, Dz1Str displayServiceName, Dz1Str exePath, Dz1Str description, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1DaemonServiceStart(Dz1Str serviceName, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1DaemonServiceStop(Dz1Str serviceName, Dz1Error *err);
DZ1_CPPLINK bool_t Dz1DaemonServiceDelete(Dz1Str serviceName, Dz1Error *err);
#endif

DZ1_CPPLINK bool_t Dz1Daemon_getMyPath(TCHAR *path, size_t path_len, TCHAR *name_ext, size_t name_ext_len, Dz1Str argv0, Dz1Error *err);

typedef void (*UserApiF)(void *ptr);
DZ1_CPPLINK bool_t Dz1DaemonMain(Dz1Str ServiceName, Dz1Str InitialPath, UserApiF Perform, UserApiF Stop, void *ptr, Dz1Error *err);

#endif

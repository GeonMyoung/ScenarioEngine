#ifndef DZ1_TERMIO_ANSI_H_LOCAL
#define DZ1_TERMIO_ANSI_H_LOCAL

#include "dz1_termio.h"

DZ1_CPPLINK_VAR Dz1ConsoleTermSpecA ansiSpecA;
#ifndef UNIX_SYSTEM
DZ1_CPPLINK_VAR Dz1ConsoleTermSpecW ansiSpecW;
#endif
#endif

#ifndef DZ1_TERMCAP_XTERM_H
#define DZ1_TERMCAP_XTERM_H

#include "dz1_termio.h"

DZ1_CPPLINK_VAR Dz1ConsoleTermSpecA xtermSpecA;
#ifndef UNIX_SYSTEM
DZ1_CPPLINK_VAR Dz1ConsoleTermSpecW xtermSpecW;
#endif
#endif

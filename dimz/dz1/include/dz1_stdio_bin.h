#ifndef DZ1_STDIO_BIN_H
#define DZ1_STDIO_BIN_H

#include <dz1_stdio.h>

DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary_save(Dz1Binary *p, FILE *fp, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t Dz1Binary_load(Dz1Binary *p, FILE *fp, Dz1Error *err);

#endif


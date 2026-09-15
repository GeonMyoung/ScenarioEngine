#ifndef DZ1_CONSOLE_PLATFORM_H
#define DZ1_CONSOLE_PLATFORM_H

#include <dz1_error.h>
#include <dz1_thread_stdio.h>

typedef struct Dz1ConsolePlatform
{
	void *priv;
	void (*priv_del)(void *prov);
	Dz1ThreadIOWaitF wait;
	Dz1ThreadIOGetChF getch;
	Dz1ThreadIOWriteF write;
} Dz1ConsolePlatform;
DZ1_CPPLINK Dz1ConsolePlatform *Dz1ConsolePlatform_new(void *priv, void (*priv_del)(void *priv),
													   Dz1ThreadIOWaitF wait,
													   Dz1ThreadIOGetChF getch,
													   Dz1ThreadIOWriteF write,
													   Dz1Error *err);
DZ1_CPPLINK void Dz1ConsolePlatform_del(Dz1ConsolePlatform *p);
static __inline__ void Dz1ConsolePlatform_delAndSetNull(void *ptr)
{
	Dz1ConsolePlatform **p = (Dz1ConsolePlatform **)ptr;
	Dz1ConsolePlatform_del(*p); *p = NULL;
}


DZ1_CPPLINK struct Dz1Console *Dz1ConsoleTTY_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *err);
DZ1_CPPLINK Dz1Error Dz1ConsoleTTY_sizeTraceOn(struct Dz1Console *con);
DZ1_CPPLINK void Dz1ConsoleTTY_sizeTraceOff(struct Dz1Console *con);

#endif

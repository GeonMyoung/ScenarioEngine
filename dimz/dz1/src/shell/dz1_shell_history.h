#ifndef DZ1_SHELL_HISTORY_H
#define DZ1_SHELL_HISTORY_H

#include <dz1_error.h>
#include <dz1_fifo.h>

typedef struct Dz1ShellHistoryA
{
	void		*fifo;
	void		*fifoc;
	u32_t		 num;
	Dz1Error	 (*push)(struct Dz1ShellHistoryA *p, str_t cmd);
	str_t		 (*pop)(struct Dz1ShellHistoryA *p, Dz1Error *err);

	u32_t		 (*count)(struct Dz1ShellHistoryA *p);
	bool_t		 (*isFull)(struct Dz1ShellHistoryA *p);

	void		 (*cursorInit)(struct Dz1ShellHistoryA *p, Dz1FifoCursorPos pos);
	bool_t		 (*cursorCond)(struct Dz1ShellHistoryA *p);
	void		 (*cursorNext)(struct Dz1ShellHistoryA *p, bool_t notNull);
	void		 (*cursorPrev)(struct Dz1ShellHistoryA *p, bool_t notNull);
	str_t		 (*cursorData)(struct Dz1ShellHistoryA *p);
} Dz1ShellHistoryA;

DZ1_CPPLINK Dz1ShellHistoryA *Dz1ShellHistoryA_new(u32_t size, Dz1Error *err);
DZ1_CPPLINK void Dz1ShellHistoryA_del(Dz1ShellHistoryA *p);
DZ1_CPPLINK void Dz1ShellHistoryA_dump(Dz1ShellHistoryA *p, int tab);

static __inline__ void Dz1ShellHistoryA_delAndSetNull(void *ptr)
{
	Dz1ShellHistoryA **p = (Dz1ShellHistoryA **)ptr;
	Dz1ShellHistoryA_del(*p); *p = NULL;
}

#ifndef UNIX_SYSTEM
typedef struct Dz1ShellHistoryW
{
	void		*fifo;
	void		*fifoc;
	u32_t		 num;
	Dz1Error	 (*push)(struct Dz1ShellHistoryW *p, wstr_t cmd);
	wstr_t		 (*pop)(struct Dz1ShellHistoryW *p, Dz1Error *err);

	u32_t		 (*count)(struct Dz1ShellHistoryW *p);
	bool_t		 (*isFull)(struct Dz1ShellHistoryW *p);

	void		 (*cursorInit)(struct Dz1ShellHistoryW *p, Dz1FifoCursorPos pos);
	bool_t		 (*cursorCond)(struct Dz1ShellHistoryW *p);
	void		 (*cursorNext)(struct Dz1ShellHistoryW *p, bool_t notNull);
	void		 (*cursorPrev)(struct Dz1ShellHistoryW *p, bool_t notNull);
	wstr_t		 (*cursorData)(struct Dz1ShellHistoryW *p);
} Dz1ShellHistoryW;

DZ1_CPPLINK Dz1ShellHistoryW *Dz1ShellHistoryW_new(u32_t size, Dz1Error *err);
DZ1_CPPLINK void Dz1ShellHistoryW_del(Dz1ShellHistoryW *p);
DZ1_CPPLINK void Dz1ShellHistoryW_dump(Dz1ShellHistoryW *p, int tab);

static __inline__ void Dz1ShellHistoryW_delAndSetNull(void *ptr)
{
	Dz1ShellHistoryW **p = (Dz1ShellHistoryW **)ptr;
	Dz1ShellHistoryW_del(*p); *p = NULL;
}
#endif

#endif

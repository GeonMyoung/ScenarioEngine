#ifndef DZ1_SHELL_INPUT_H_LOCAL
#define DZ1_SHELL_INPUT_H_LOCAL

#include <dz1_termio.h>

typedef enum
{
	Dz1ShellInputStatus_ok,
	Dz1ShellInputStatus_esc,
	Dz1ShellInputStatus_up,
	Dz1ShellInputStatus_down,
	Dz1ShellInputStatus_right,
	Dz1ShellInputStatus_left,
	Dz1ShellInputStatus_pageUp,
	Dz1ShellInputStatus_pageDown,
	Dz1ShellInputStatus_tab,
	Dz1ShellInputStatus_notSupport,
	Dz1ShellInputStatus_max
} Dz1ShellInputStatus;

#define DZ1_SHELL_INPUT_BUF_SIZE		65535
typedef struct Dz1ShellInputA
{
	char  buf[DZ1_SHELL_INPUT_BUF_SIZE];
	char *cursor;
	char *end;
	void *termio;
} Dz1ShellInputA;

static __inline__ Dz1Error Dz1ShellInputA_init(Dz1ShellInputA *p, str_t termName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) { ERR_SET_OUT(&err, EINVAL); }
	else if ((p->termio = Dz1TermIoA_new(termName, 64, &err)) == NULL) { ERR_OUT(&err); }
	else
	{
		memset(p->buf, 0, sizeof(char) * DZ1_SHELL_INPUT_BUF_SIZE);
		p->cursor = p->buf;
		p->end = p->buf;
	}
	return err;
}

static __inline__ void Dz1ShellInputA_clean(Dz1ShellInputA *p)
{
	if (p->termio) Dz1TermIoA_del(p->termio);
}

DZ1_CPPLINK Dz1ShellInputStatus Dz1ShellInputA_recv(Dz1ShellInputA *p, str_t defStr);

#ifndef UNIX_SYSTEM
typedef struct Dz1ShellInputW
{
	wchar_t  buf[DZ1_SHELL_INPUT_BUF_SIZE];
	wchar_t *cursor;
	wchar_t *end;
	void	*termio;
} Dz1ShellInputW;

static __inline__ Dz1Error Dz1ShellInputW_init(Dz1ShellInputW *p, wstr_t termName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (!p) { ERR_SET_OUT(&err, EINVAL); }
	else if ((p->termio = Dz1TermIoW_new(termName, 64, &err)) == NULL) { ERR_OUT(&err); }
	else
	{
		memset(p->buf, 0, sizeof(wchar_t) * DZ1_SHELL_INPUT_BUF_SIZE);
		p->cursor = p->buf;
		p->end = p->buf;
	}
	return err;
}

static __inline__ void Dz1ShellInputW_clean(Dz1ShellInputW *p)
{
	if (p->termio) Dz1TermIoW_del(p->termio);
}

DZ1_CPPLINK Dz1ShellInputStatus Dz1ShellInputW_recv(Dz1ShellInputW *p, wstr_t defStr);
#endif

#endif

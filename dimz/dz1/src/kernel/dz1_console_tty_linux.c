#include <dz1.h>
//#define WIN32_DEBUG
#if defined(UNIX_SYSTEM) || defined(WIN32_DEBUG)

#ifdef UNIX_SYSTEM
#include <termios.h>
#include <sys/ioctl.h>
#endif

#include "dz1_console.h"






#ifdef WIN32
struct winsize
{
	int ws_col;
	int ws_row;
};

struct termios
{
	int dumb;
	int c_lflag;
	int c_cc[16];
};
int tcsetattr();
int tcgetattr();
int close();
int read(int, unsigned char *, int);
int write(int, unsigned char *, int);
int dup(int);
int ioctl(int, int, void *);
#define TIOCGWINSZ			0

#define TCSAFLUSH			0
#define ECHO				1
#define ICANON				2

#define VMIN				1
#define VTIME				2

#define SIGWINCH			0
#endif // WIN32






static OutputHook outputHook = NULL;
static void *outputHookParam = NULL;

void Dz1OutputHook_set(OutputHook func, void *param)
{
	outputHook = func;
	outputHookParam = param;
}

typedef struct Dz1ConsolePlatformLinux
{
	int con_in;
	int con_out;
	struct termios term;
} Dz1ConsolePlatformLinux;

static void Dz1ConsolePlatformLinux_del(Dz1ConsolePlatformLinux *p)
{
	if (!p) return;
	printf("Dz1ConsolePlatformLinux_del() : Terminal Restore\n"); fflush(stdout);
	tcsetattr(p->con_out, TCSAFLUSH, &p->term);
	if (p->con_in != -1) close(p->con_in);
	if (p->con_out != -1) close(p->con_out);

	free(p);
}

static void Dz1ConsolePlatformLinux_delAndSetNull(void *ptr)
{
	Dz1ConsolePlatformLinux **p = (Dz1ConsolePlatformLinux **)ptr;
	Dz1ConsolePlatformLinux_del(*p); *p = NULL;
}

static Dz1Error Dz1ConsolePlatformLinux_setup(Dz1ConsolePlatformLinux *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (tcgetattr(p->con_out, &p->term) < 0) { }
	else
	{
		struct termios temp = p->term;
		temp.c_lflag &= ~(ECHO | ICANON);
		temp.c_cc[VMIN] = 0;
		temp.c_cc[VTIME] = 0;
		if (tcsetattr(p->con_out, TCSAFLUSH, &temp) < 0) Dz1Error_set(&err, errno);
	}

	return err;
}

static Dz1ConsolePlatformLinux *Dz1ConsolePlatformLinux_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *errp)
{
	Dz1ConsolePlatformLinux *ret = (Dz1ConsolePlatformLinux *)calloc(sizeof(Dz1ConsolePlatformLinux), 1);
	if (ret == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		ret->con_in = ret->con_out = -1;
		pthread_cleanup_push(Dz1ConsolePlatformLinux_delAndSetNull, (void *)&ret);

		if ((ret->con_in = dup(con_in)) < 0)		{ Dz1Error_set(errp, errno); no_con_err_out("Dz1ConsolePlatformLinux_new", "con_in dup fail"); }
		else if ((ret->con_out = dup(con_out)) < 0)	{ Dz1Error_set(errp, errno); no_con_err_out("Dz1ConsolePlatformLinux_new", "con_out dup fail"); }
		else if ((*errp = Dz1ConsolePlatformLinux_setup(ret)).code) no_con_err_out("Dz1ConsolePlatformLinux_new", "platform console setup fail");
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1ConsolePlatformLinux_delAndSetNull, (void *)&ret);
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Linux TTY Console
///////////////////////////////////////////////////////////////////////////////
static Dz1Error Dz1ConsoleLinuxTTY_waitIn(Dz1ConsolePlatformLinux *p, s32_t wait_us)
{
	s32_t _wait_us, status;
	struct timeval to;
	fd_set rd;

	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	do
	{
		_wait_us = wait_us < 0 ?	100000 :						// Unlimited wait
									wait_us > 200000 ? 100000 :		// Unit time wait
													  wait_us;		// remain time wait

		to.tv_sec = 0; to.tv_usec = _wait_us; FD_ZERO(&rd); FD_SET(p->con_in, &rd);

		if ((status = select(p->con_in + 1, &rd, NULL, NULL, &to)) < 0) Dz1Error_set(&err, errno);
		else if (status == 0) { wait_us = wait_us > 0 ? wait_us - _wait_us : wait_us; Dz1Error_set(&err, ETIMEDOUT); }
		else { Dz1Error_set(&err, 0); break; }
	}
	while(wait_us);

	return err;
}

static Dz1Error Dz1ConsoleLinuxTTY_waitOut(Dz1ConsolePlatformLinux *p, s32_t wait_us)
{
	s32_t _wait_us, status;
	struct timeval to;
	fd_set wd;

	Dz1Error err = DZ1_ERROR_INITIALIZER;

	while(wait_us)
	{
		_wait_us = wait_us < 0 ?	100000 :						// Unlimited wait
									wait_us > 200000 ? 100000 :		// Unit time wait
													  wait_us;		// remain time wait

		to.tv_sec = 0; to.tv_usec = _wait_us; FD_ZERO(&wd); FD_SET(p->con_out, &wd);

		if ((status = select(p->con_out + 1, NULL, &wd, NULL, &to)) < 0) Dz1Error_set(&err, errno);
		else if (status == 0) { wait_us = wait_us > 0 ? wait_us - _wait_us : wait_us; Dz1Error_set(&err, ETIMEDOUT); }
		else { Dz1Error_set(&err, 0); break; }
	}

	return err;
}

static Dz1Error Dz1ConsoleLinuxTTY_wait(void *ptr, Dz1ThreadIODir flag, s32_t wait_us)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1ConsolePlatformLinux *priv = (Dz1ConsolePlatformLinux *)ptr;
	switch(flag)
	{
		case Dz1ThreadIODir_in:
			err = Dz1ConsoleLinuxTTY_waitIn(priv, wait_us);
			break;
		case Dz1ThreadIODir_out:
			err = Dz1ConsoleLinuxTTY_waitOut(priv, wait_us);
			break;
		default:
			Dz1Error_set(&err, EINVAL);
			break;
	}
	return err;
}

/*
static ssize_t Dz1ConsoleLinuxTTY_read(void *ptr, u8_t *buf, size_t buf_size, s32_t wait_us, Dz1Error *errp)
{
	ssize_t ret = -1;
//	Dz1ConsolePlatform *platform = con->platform;
	Dz1ConsolePlatformLinux *p = (Dz1ConsolePlatformLinux *)ptr;

	if ((*errp = Dz1ConsoleLinuxTTY_waitIn(p, wait_us)).code == 0)
	{
		if ((ret = read(p->con_in, buf, buf_size)) < 0) Dz1Error_set(errp, errno);
	}
	return ret;
}
*/

static int Dz1ConsoleLinuxTTY_getch(void *ptr, s32_t wait_us, Dz1Error *errp)
{
	ssize_t ret = -1;
//	Dz1ConsolePlatform *platform = con->platform;
	Dz1ConsolePlatformLinux  *p = (Dz1ConsolePlatformLinux *)ptr;

	if ((*errp = Dz1ConsoleLinuxTTY_waitIn(p, wait_us)).code == 0)
	{
		ssize_t sz = 0;
		u8_t buf[8];
		if ((sz= read(p->con_in, buf, 1)) < 0) Dz1Error_set(errp, errno);
		else ret = (int)buf[0];
	}
	return ret;
}

ssize_t Dz1ConsoleLinuxTTY_write(void *ptr, u8_t *data, size_t data_size, s32_t wait_us, Dz1Error *err)
{
	ssize_t ret = -1;
	Dz1Error _err, *errp = err ? err : &_err;
//	Dz1ConsolePlatform *platform = con->platform;
	Dz1ConsolePlatformLinux  *p = (Dz1ConsolePlatformLinux *)ptr;

	if ((*errp = Dz1ConsoleLinuxTTY_waitOut(p, wait_us)).code == 0)
	{
		if ((ret = write(p->con_out, data, data_size)) < 0) Dz1Error_set(errp, errno);

	}
	if (outputHook != NULL) outputHook(outputHookParam, data, data_size);

	return ret;
}

// static void Dz1ConsoleLinuxTTY_del(Dz1ConsolePlatform *p)
// {
// 	if (!p) return;
// 	if (p->priv) Dz1ConsolePlatformLinux_del((Dz1ConsolePlatformLinux *)p->priv);
// 	free(p);
// }

// static void Dz1ConsoleLinuxTTY_delAndSetNull(void *ptr)
// {
// 	Dz1ConsolePlatform **p = (Dz1ConsolePlatform **)ptr;
// 	Dz1ConsoleLinuxTTY_del(*p); *p = NULL;
// }

// static Dz1ConsolePlatform *Dz1ConsoleLinuxTTY_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *errp)
// {
// 	Dz1ConsolePlatform *ret = (Dz1ConsolePlatform *)calloc(sizeof(Dz1ConsolePlatform), 1);
// 	if (ret == NULL) { Dz1Error_set(errp, ENOMEM); }
// 	else
// 	{
// 		pthread_cleanup_push(Dz1ConsoleLinuxTTY_delAndSetNull, (void *)&ret);
// 
// 		if ((ret->priv = Dz1ConsolePlatformLinux_new(con_in, con_out, errp)) == NULL) { printf("!!!!\n"); }
// 		else
// 		{
// 			ret->wait = Dz1ConsoleLinuxTTY_wait;
// 			//ret->read = Dz1ConsoleLinuxTTY_read;
// 			ret->getch= Dz1ConsoleLinuxTTY_getch;
// 			ret->write = Dz1ConsoleLinuxTTY_write;
// 			Dz1Error_set(errp, 0);
// 		}
// 		pthread_cleanup_pop(errp->code); // (Dz1ConsoleLinuxTTY_delAndSetNull, (void *)&ret);
// 	}
// 	return ret;
// }

///////////////////////////////////////////////////////////////////////////////
// General Console Interface
///////////////////////////////////////////////////////////////////////////////
Dz1Console *Dz1ConsoleTTY_new(Dz1FileDescr con_in, Dz1FileDescr con_out, Dz1Error *err)
{
	Dz1Error _err, *errp = err ? err : &_err;
//	Dz1Console *ret = Dz1Console_new(NULL, Dz1ConsoleLinuxTTY_del, errp);
	Dz1Console *ret = Dz1Console_new(Dz1ConsolePromptMode_longTime, NULL, errp);
	if (ret == NULL) no_con_err_out("Dz1ConsoleTTY_new", "struct alloc fail");
	else
	{
		Dz1ConsolePlatform *pf = NULL;
		pthread_cleanup_push(Dz1Console_delAndSetNull, (void *)&ret);

		if ((ret->platform = pf = Dz1ConsolePlatform_new(NULL, 
														 (Dz1DelFunc)Dz1ConsolePlatformLinux_del, 
														 Dz1ConsoleLinuxTTY_wait, 
														 Dz1ConsoleLinuxTTY_getch, 
														 Dz1ConsoleLinuxTTY_write, 
														 errp)) == NULL) no_con_err_out("Dz1ConsoleTTY_new", "platform specific data creation fail");
		else if ((pf->priv = Dz1ConsolePlatformLinux_new(con_in, con_out, errp)) == NULL) { printf("!!!!\n"); }
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Console_delAndSetNull, (void *)&ret);
	}
	return ret;
}

static Dz1Console *trace = NULL;

static void Dz1ConsoleTTY_setupSize(void);
static void Dz1ConsoleTTY_sizeChange(int sig_no) { if (sig_no == SIGWINCH) Dz1ConsoleTTY_setupSize(); }

static void Dz1ConsoleTTY_setupSize(void)
{
	struct winsize size;
	if (trace && ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size) == 0)
	{
		u32_t width, height;
		if (size.ws_col <= 80) width = 80;
		else width = size.ws_col;
		height = size.ws_row;

		trace->width = width;
		trace->height = height;

	}
	signal(SIGWINCH, Dz1ConsoleTTY_sizeChange);
}

static void Dz1ConsoleTTY_sizeTraceCancel(void *ptr)
{
	if (trace) trace = NULL;
}

Dz1Error Dz1ConsoleTTY_sizeTraceOn(Dz1Console *con)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (con == NULL) Dz1Error_set(&err, EINVAL);
	else
	{
		trace = con;
		pthread_cleanup_push(Dz1ConsoleTTY_sizeTraceCancel, NULL);

		if (signal(SIGWINCH, Dz1ConsoleTTY_sizeChange) == SIG_ERR) Dz1Error_set(&err, EFAULT);
		else Dz1ConsoleTTY_setupSize();

		pthread_cleanup_pop(err.code); // (Dz1ConsoleTTY_sizeTraceCancel, NULL);
	}
	return err;
}

void Dz1ConsoleTTY_sizeTraceOff(Dz1Console *con)
{
	if (trace && trace == con) { trace = NULL; }
	signal(SIGWINCH, SIG_DFL);
}

#endif
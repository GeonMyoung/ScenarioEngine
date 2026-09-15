#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#if defined(LINUX)
#include <termios.h>
#elif defined(WIN32)
#endif

#include <hae_output.h>
#include <hae_local_thread.h>
#include <hae_local_memory.h>
#include <hae_tvfunc.h>
#include <hae_misc.h>

#include <hae_serial_io.h>
#define DBG_OUT(err)	HaeOut->printf(0, __FILE__ ":%d = %s(%d)\n", __LINE__, strerror((err)), (err))


#if defined(LINUX)
typedef struct HaeSerialHandle
{
	str_t devname;
	int fd;
	int baud;
	int dataBit;
	int flowCtl;
	struct termios backup_tios;
} HaeSerialHandle;

static HaeSerialHandle *haeSerialHandle_create(str_t devname, int fd, int baud, int dataBit, int flowCtl, int *err)
{
	HaeSerialHandle *ret = (HaeSerialHandle *)LOCAL_MALLOC(sizeof(HaeSerialHandle));
	if (ret)
	{
		if ((ret->devname = haeMiscStr_cloneToLocal(devname, err)) == NULL)
		{
			*err = ENOMEM;
			LOCAL_FREE(ret);
			ret = NULL;
		}
		else
		{
			ret->fd = fd;
			// Backup Original TTY Setting
			if (tcgetattr(ret->fd, &ret->backup_tios) < 0)
			{
				*err = errno;
				LOCAL_FREE(ret);
				ret = NULL;
			}
			else
			{
				ret->baud = baud;
				ret->dataBit = dataBit;
				ret->flowCtl = flowCtl;
				*err = 0;
			}
		}
	}
	else
		*err = ENOMEM;
	return ret;
}

static void haeSerialHandle_del(HaeSerialHandle *p)
{
	if (p)
	{
		if (p->devname) LOCAL_FREE(p->devname);
		LOCAL_FREE(p);
	}
}

struct speed {
	int speed_int, speed_val;
};

static struct speed speeds[] = {
#ifdef B110
	{ 110, B110 },
#endif
#ifdef B300
	{ 300, B300 },
#endif
#ifdef B600
	{ 600, B600 },
#endif
#ifdef B1200
	{ 1200, B1200 },
#endif
#ifdef B2400
	{ 2400, B2400 },
#endif
#ifdef B4800
	{ 4800, B4800 },
#endif
#ifdef B9600
	{ 9600, B9600 },
#endif
#ifdef B14400
	{ 14400, B14400 },
#endif
#ifdef B19200
	{ 19200, B19200 },
#endif
#ifdef B38400
	{ 38400, B38400 },
#endif
#ifdef B57600
	{ 57600, B57600 },
#endif
#ifdef B115200
	{ 115200, B115200 },
#endif
#ifdef B230400
	{ 230400, B230400 },
#endif
#ifdef B460800
	{ 460800, B460800 },
#endif
	{ 0, 0 }
};

static int translate_speed (int bps)
{
	struct speed *speedp;

	if (bps != 0) {
		for (speedp = speeds; speedp->speed_int; speedp++) {
			if (bps == speedp->speed_int)
				return speedp->speed_val;
		}
	}
	return B38400;
}

static HaeSerialHandle *open_serial(str_t portName, int baud, int dataBit, int flowCtl, int *err)
{
	HaeSerialHandle *ret = NULL;
	// Open with Non Blocked Mode
	int fd = 0;
	//HaeOut->printf(0, "open_serial() : %s\n", portName);
	fd = open(portName, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd < 0)
		*err = errno;
	else if ((ret = haeSerialHandle_create(portName, fd, baud, dataBit, flowCtl, err)) == NULL)
		close(fd);
	return ret;
}

static int setup_serial(HaeSerialHandle *p)
{
	int flag = 0, baudRate = 0, dataBit = 0;
	struct termios tios = p->backup_tios;
	// Make sure Blocking Mode for SUN Solaris System
	if (fcntl(p->fd, F_SETFL, flag & ~O_NONBLOCK) < 0) return errno;


	switch(p->dataBit)
	{
		case 5: dataBit = CS5; break;
		case 6: dataBit = CS6; break;
		case 7: dataBit = CS7; break;
		case 8: dataBit = CS8; break;
	}

	tios.c_cflag     &= ~(CSIZE | CSTOPB | PARENB | CLOCAL);
	tios.c_cflag     |= dataBit | CREAD | HUPCL;

	tios.c_iflag      = IGNBRK | IGNPAR;
	tios.c_oflag      = 0;
	tios.c_lflag      = 0;
	tios.c_cc[VMIN]   = 1;
	tios.c_cc[VTIME]  = 0;

	if (p->flowCtl == HAE_SERIAL_FLOW_NONE)
		tios.c_cflag &= ~CRTSCTS;
	else
	{
		if (p->flowCtl & HAE_SERIAL_FLOW_CRTSCTS)
			tios.c_cflag |= CRTSCTS;

		if (p->flowCtl & HAE_SERIAL_FLOW_XONXOFF)
		{
			tios.c_iflag     |= IXON | IXOFF;
			tios.c_cc[VSTOP]  = 0x13;   /* DC3 = XOFF = ^S */
			tios.c_cc[VSTART] = 0x11;   /* DC1 = XON  = ^Q */
		}
	}

	baudRate = translate_speed(p->baud);
	cfsetospeed (&tios, baudRate);
	cfsetispeed (&tios, baudRate);

	if (tcsetattr(p->fd, TCSAFLUSH, &tios) < 0)
	{
		int err = errno;
		tcsetattr(p->fd, TCSAFLUSH, &p->backup_tios);
		return err;
	}
	return 0;
}

static int wait_serial(HaeSerialHandle *p, struct timeval *to, int *err)
{
	int ret = 0;
	struct timeval unit_to = { 0, 100000 }, _to;
	fd_set rd;

	*err = 0;

	if (!to)
	{
		do
		{
			FD_ZERO(&rd); FD_SET(p->fd, &rd);
			_to = unit_to;
			pthread_testcancel();
			ret = select(p->fd + 1, &rd, NULL, NULL, &_to);
			pthread_testcancel();
		} while(ret == 0);
		if (ret < 0) *err = errno;
	}
	else
	{
		struct timeval temp;
		while(!hae_tvfunc_isZero(*to))
		{
			FD_ZERO(&rd); FD_SET(p->fd, &rd);
			if (hae_tvfunc_cmp(*to, unit_to) > 0) _to = unit_to;
			else _to = *to;
			temp = _to;

			pthread_testcancel();
			ret = select(p->fd + 1, &rd, NULL, NULL, &_to);
			pthread_testcancel();

			if (ret == 0) *to = hae_tvfunc_reduce(*to, temp);
			else break;
		}
		if (ret == 0) *err = ETIMEDOUT;
		else if (ret < 0) *err = errno;
	}
	return ret;
}

static int send_serial(HaeSerialHandle *p, u8_t *data, u32_t size, int *err)
{
	int ret = write(p->fd, data, size);
	if (ret < 0) { *err = errno; DBG_OUT(*err); }
	else if (ret == 0) { *err = EPIPE; DBG_OUT(*err); }
	else
	{
		*err = 0;
//		HaeOut->printf(0, "send_serial() >>>>>>>>>>>>>>>\n");
//		HaeOut->printb(1, data, size);
	}
	return ret;
}

static int recv_serial(HaeSerialHandle *p, u8_t *buffer, u32_t size, int *err)
{
	int ret = read(p->fd, buffer, size);
	if (ret < 0) { *err = errno; DBG_OUT(*err); }
	else if (ret == 0) { *err = EPIPE; DBG_OUT(*err); }
	else
	{
		*err = 0;
//		HaeOut->printf(0, "recv_serial() <<<<<<<<<<<<<<<\n");
//		HaeOut->printb(1, buffer, ret);
	}
	return ret;
}

static void close_serial(HaeSerialHandle *p)
{
	if (p)
	{
		if (p->fd != 0 && p->fd != 1 && p->fd != 2) close(p->fd);
		tcsetattr(p->fd, TCSAFLUSH, &p->backup_tios);
		haeSerialHandle_del(p);
	}
}

#elif defined(WIN32)
#endif

void *hae_serial_open(int port, unsigned int baud, int dataBit, int flowCtl, int *err)
{
#if defined(LINUX)
	str_t portNames[] = { "/dev/ttyS0", "/dev/ttyS1", "/dev/ttyS2", "/dev/ttyS3" };
#elif defined(WIN32)
	str_t portNames[] = { "COM1", "COM2", "COM3", "COM4" };
#endif
	if (port < 0 || port > 3) { *err = EINVAL; return NULL; }
	return hae_serial_openPortName(portNames[port], baud, dataBit, flowCtl, err);
}

void *hae_serial_openPortName(str_t portName, unsigned int baud, int dataBit, int flowCtl, int *err)
{
	int local_err, *errp = err ? err : &local_err;

	HaeSerialHandle *ret = NULL;

	if (!portName || !strlen(portName)) { *errp = EINVAL; return NULL; }
	switch(baud)
	{
		case 110: case 300: case 600: case 1200:
		case 2400: case 4800: case 9600: case 14400:
		case 19200: case 38400: case 57600: case 115200:
		case 230400: case 460800:
			break;
		default:
			*errp = EINVAL;
			return NULL;
	}

	switch(dataBit)
	{
		case 5: case 6: case 7: case 8:
			break;
		default:
			*errp = EINVAL;
			return NULL;
	}

	if ((ret = open_serial(portName,  baud, dataBit, flowCtl, errp)))
	{
		int status = 0;
		if ((status = setup_serial(ret)))
		{
			close_serial(ret); ret = NULL;
			*errp = status;
		}
	}
	return ret;
}

int hae_serial_wait(void *handle, struct timeval *to, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	HaeSerialHandle *p = (HaeSerialHandle *)handle;
	return wait_serial(p, to, errp);
}

int hae_serial_send(void *handle, u8_t *data, u32_t size, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	HaeSerialHandle *p = (HaeSerialHandle *)handle;
	return send_serial(p, data, size, errp);
}

int hae_serial_recv(void *handle, u8_t *buffer, u32_t size, int *err)
{
	int local_err, *errp = err ? err : &local_err;
	HaeSerialHandle *p = (HaeSerialHandle *)handle;
	return recv_serial(p, buffer, size, errp);
}

void hae_serial_close(void *handle)
{
	HaeSerialHandle *p = (HaeSerialHandle *)handle;
	close_serial(p);
}

typedef struct HaeSerialMonitorArg
{
	HaeSerialHandle *handle;
	HaeSerialRecvHandlerFunc func;
	void *func_arg;
} HaeSerialMonitorArg;

static HaeSerialMonitorArg *haeSerialMonitorArg_create(	HaeSerialHandle *handle,
														HaeSerialRecvHandlerFunc func,
														void *func_arg, int *err)
{
	HaeSerialMonitorArg *ret = (HaeSerialMonitorArg *)LOCAL_MALLOC(sizeof(HaeSerialMonitorArg));
	if (!ret) *err = ENOMEM;
	else
	{
		ret->handle = handle;
		ret->func = func;
		ret->func_arg = func_arg;
		*err = 0;
	}
	return ret;
}

static void haeSerialMonitorArg_del(HaeSerialMonitorArg *p)
{
	if (p)
	{
		//if (p->handle) hae_serial_close(p->handle);
		LOCAL_FREE(p);
	}
}

static void *serial_monitor(void *arg)
{
	int err = 0, status = 0;
	HaeSerialMonitorArg *p = (HaeSerialMonitorArg *)arg;
	struct timeval to = { 0, 100000 };
	pthread_cleanup_push((HaeGeneralDelFunc)haeSerialMonitorArg_del, (void *)p);
	while(1)
	{
		to.tv_sec = 0; to.tv_usec = 100000;
		while((status = hae_serial_wait(p->handle, &to, &err)) == 0) { to.tv_sec = 0; to.tv_usec = 100000; }
		if (status > 0)
		{
			if ((err = p->func(p->handle, p->func_arg)))
				break;
		}
		else if (status < 0)
		{
			break;
		}
	}
	pthread_cleanup_pop(1); // (HaeGeneralDelFunc)haeSerialMonitorArg_del, (void *)p);
	while(1)
	{
		pthread_testcancel();
		haeMisc_usleep(100000);
		pthread_testcancel();
	}
	return NULL;
}

int hae_serial_io_monitor_start(void *handle, HaeSerialRecvHandlerFunc func, void *func_arg, int *err)
{
	int id = -1;
	int local_err, *errp = err ? err : &local_err;
	if (!handle || !func) *errp = EINVAL;
	else
	{
		HaeSerialMonitorArg *arg = haeSerialMonitorArg_create(handle, func, func_arg, errp);
		if (arg)
		{
			if (!(*errp = HaeLocalThreadManager->START(&id, serial_monitor, (void *)arg, HAE_THREAD_LOG_ERROR)))
				*errp = 0;
			else
				haeSerialMonitorArg_del(arg);
		}
		else
			hae_serial_close(handle);
	}
	return id;
}

int hae_serial_io_monitor_stop(int id)
{
	return HaeLocalThreadManager->stop(id, NULL, HAE_THREAD_STOP_BLOCKED);
}

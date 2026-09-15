#include <errno.h>

#include <pthread.h>
#include "hae_misc.h"

#include "hae_output.h"

typedef struct HaeOutputLocal
{
	void (*vfprintf)(FILE *out, int tab, char *fmt, va_list ap);
	void (*fprintf)(FILE *out, int tab, char *fmt, ...);
	void (*fprintb)(FILE *out, int tab, void *buf, u32_t size);

	void (*vprintf)(int tab, char *fmt,va_list ap); 
	void (*printf)(int tab, char *fmt, ...);
	void (*printb)(int tab, void *buf, u32_t size);

	int (*change)(FILE *new_output);

	void (*getSize)(u16_t *width, u16_t *height);
	void (*setSize)(u16_t *width, u16_t *height);

	void (*setLF)(int mode);

	void (*setFullTimeHeader)(void);
	void (*setComapctTimeHeader)(void);

	FILE *output;
	pthread_mutex_t lock;
	u16_t width, height;
	int mode;
} HaeOutputLocal;

static str_t print_date_full(char *dst)
{
	time_t now = time(NULL);
	struct tm *tm_p = localtime(&now);
	struct tm tm = *tm_p;
	sprintf(dst, "[%02d-%02d-%02d %02d:%02d:%02d] ",
			(tm.tm_year + 1900) % 100, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	return dst;
}

static str_t print_data_hhmmss(char *dst)
{
	time_t now = time(NULL);
	struct tm *tm_p = localtime(&now);
	struct tm tm = *tm_p;
	sprintf(dst, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return dst;
}

static int dateMode = 0;
struct DateMode
{
	int print_size;
	str_t (*print)(char *dst);
} DateMode[] =
{
	{ 20, print_date_full },
	{ 10, print_data_hhmmss }
};

static int chk_fmt(char *fmt)
{
	int ret = 0;
	char *cp = fmt;
	while(*cp)
	{
		if (*cp == '\n' && *(cp+1) != '\0') ret++;
		cp++;
	}
	return ret;
}

static int fmt_cnv(char *buf, char *fmt, int last_new_line, int tab)
{
	int ret = 0;
	char *bp = buf, *fp = fmt;

	if (last_new_line) { DateMode[dateMode].print(bp); bp += DateMode[dateMode].print_size; }

	while(tab--) { sprintf(bp, "    "); bp+=4; }

	while(*fp)
	{
		*bp++ = *fp;
		if (*fp == '\n')
		{
			if (*(fp + 1) != '\0')
			{
				DateMode[dateMode].print(bp);
				bp += DateMode[dateMode].print_size;
			}
			else
			{
				ret = TRUE;
				break;
			}
		}
		fp++;
	}
	*bp = '\0';
	return ret;
}

static void haeOutput_core_buf_cancel(void *p) { free(p); }

static void mutex_unlock(void *arg)
{
	pthread_mutex_t *lock = (pthread_mutex_t *)arg;
	pthread_mutex_unlock(lock);
}

#define OUTPUT_BUFFER_SIZE		0x4000 // 16384
static void haeOutput_core(FILE *target_file, int mode, int tab, char *fmt, va_list ap)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;

	static int last_new_line = TRUE;

	int len;
	int num_of_nl;
	char *buf = NULL;
	char target[OUTPUT_BUFFER_SIZE];
	char *tp = target;

	if (!target_file) return;

	if (!fmt || !(len = strlen(fmt))) return;

	num_of_nl = chk_fmt(fmt);

	if ((buf = (char *)malloc((last_new_line ? DateMode[dateMode].print_size : 0) + 
								tab * 4 +
								len + 
								(num_of_nl * DateMode[dateMode].print_size) + 1)) == NULL) { }
	else
	{
		pthread_cleanup_push(haeOutput_core_buf_cancel, (void *)buf);

		last_new_line = fmt_cnv(buf, fmt, last_new_line, tab);

#ifndef WIN32
		vsnprintf(target, OUTPUT_BUFFER_SIZE, buf, ap);
#else
		vsprintf(target, buf, ap);
#endif
		pthread_cleanup_pop(1); // (haeOutput_core_buf_cancel, (void *)buf);

		pthread_mutex_lock(&p->lock);
		pthread_cleanup_push(mutex_unlock, (void *)&p->lock);

		while(*tp)
		{
			if (*tp == '\n' && mode == HAE_OUTPUT_CRLF) putc('\r', target_file);
			putc(*tp++, target_file);
		}
		fflush(target_file);

		pthread_cleanup_pop(1); // (mutex_unlock, (void *)&p->lock);
	}
}

static void _fprintf(FILE *target_out, int tab, char *fmt, ...)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	va_list ap;
	va_start(ap, fmt);

	haeOutput_core(target_out ? target_out : p->output ? p->output : stdout, p->mode, tab, fmt, ap);

	va_end(ap);
}

static void haeOutput_binLineDump(FILE *fp, u8_t *data,u32_t length)
{
	u32_t i;
	for (i = 0; i < length; i++) _fprintf(fp, 0, "%02x ",data[i]);
	if (length < 16) for (i = length; i < 16; i++) _fprintf(fp, 0, "   ");
	_fprintf(fp, 0, "  ");
	for (i = 0; i < length; i++) _fprintf(fp, 0, "%c",data[i] < 32 || (data[i] & 0x80) || isDangerChar(data[i]) ? '.' : data[i]);
	_fprintf(fp, 0, "\n");
}

static void haeOutput_binDump(FILE *fp, int tab, void *d, u32_t length)
{
	u8_t *data = (u8_t *)d;
	s32_t offset=0;
	_fprintf(fp, tab, "Binary Dump at [0x%p][%u]\n",data, length);
	while(length>16)
	{
		_fprintf(fp, tab, "%08x : ",offset);
		haeOutput_binLineDump(fp, data, 16);
		data+=16;
		offset+=16;
		length-=16;
	}
	_fprintf(fp, tab, "%08x : ",offset);
	haeOutput_binLineDump(fp, data, length);
}

static void haeOutput_printb(int tab, void *d, u32_t len)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	haeOutput_binDump(p->output ? p->output : stdout, tab, d, len);
}

static void haeOutput_fprintb(FILE *fp, int tab, void *d, u32_t len)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	haeOutput_binDump(fp ? fp : p->output ? p->output : stdout, tab, d, len);
}

static void haeOutput_vfprintf(FILE *target_out, int tab, char *fmt, va_list ap)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	haeOutput_core(target_out ? target_out : p->output ? p->output : stdout, p->mode, tab, fmt, ap);
}

static void haeOutput_vprintf(int tab, char *fmt, va_list ap)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	haeOutput_core(p->output ? p->output : stdout, p->mode, tab, fmt, ap);
}

static void haeOutput_fprintf(FILE *target_out, int tab, char *fmt, ...)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	va_list ap;
	va_start(ap, fmt);

	haeOutput_core(target_out ? target_out : p->output ? p->output : stdout, p->mode, tab, fmt, ap);

	va_end(ap);
}

static void haeOutput_printf(int tab, char *fmt, ...)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	va_list ap;
	va_start(ap, fmt);

	haeOutput_core(p->output ? p->output : stdout, p->mode, tab, fmt, ap);

	va_end(ap);
}

static int haeOutput_change(FILE *new_output)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;
	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&p->lock);

	p->output = new_output;

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&p->lock);
	return 0;
}

static void haeOutput_getSize(u16_t *width, u16_t *height)
{
	u16_t _width, *w = width ? width : &_width;
	u16_t _height, *h = height ? height : &_height;

	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&p->lock);

	*w = p->width;
	if (*w > DateMode[dateMode].print_size)
		*w -= DateMode[dateMode].print_size;
	else
	{
		printf("\nhaeOutput_getSize() : p->width = %d, datemode = %d\n", p->width, DateMode[dateMode].print_size);
		*w = (u16_t)-1;
	}
	*h = p->height;

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&p->lock);
}

static void haeOutput_setSize(u16_t *width, u16_t *height)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&p->lock);

	if (width) p->width = *width;
	if (height) p->height= *height;

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&p->lock);
}

static void haeOutput_setLF(int mode)
{
	HaeOutputLocal *p = (HaeOutputLocal *)HaeOut;

	if (mode != HAE_OUTPUT_CR && mode != HAE_OUTPUT_CRLF) return;

	pthread_mutex_lock(&p->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&p->lock);

	p->mode = mode;

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&p->lock);
}

static void haeOutput_setFullTimeHeader(void) { dateMode = 0; }
static void haeOutput_setCompactTimeHeader(void) { dateMode = 1; }

HaeOutputLocal haeOutLocal =
{
	haeOutput_vfprintf,
	haeOutput_fprintf,
	haeOutput_fprintb,

	haeOutput_vprintf,
	haeOutput_printf,
	haeOutput_printb,

	haeOutput_change,

	haeOutput_getSize,
	haeOutput_setSize,

	haeOutput_setLF,

	haeOutput_setFullTimeHeader,
	haeOutput_setCompactTimeHeader,

	NULL,
	PTHREAD_MUTEX_INITIALIZER,
	80, 25,
	HAE_OUTPUT_CR
};

HaeOutput *HaeOut = (HaeOutput *)&haeOutLocal;

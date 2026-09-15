#ifndef DZ1_SYSLOGR_H
#define DZ1_SYSLOGR_H

#include <dz1_error.h>
#include <dz1_socket.h>
#include <stdarg.h>

#ifndef UNIX_SYSTEM
#define OS_MBCS_CHARSET			"EUC-KR"
#define OS_WIDE_CHARSET			"UCS-2LE"
#else
#define OS_MBCS_CHARSET			"UTF-8"
#endif
// priority number
typedef enum Dz1SyslogPri
{
	Dz1SyslogPri_EMERG		=	0,			// system is unusable
	Dz1SyslogPri_ALERT		=	1,			// action must be taken immediately
	Dz1SyslogPri_CRIT		=	2,			// critical conditions
	Dz1SyslogPri_ERR		=	3,			// error conditions
	Dz1SyslogPri_WARNING	=	4,			// warning conditions
	Dz1SyslogPri_NOTICE		=	5,			// normal but significant condition
	Dz1SyslogPri_INFO		=	6,			// informational
	Dz1SyslogPri_DEBUG		=	7,			// debug-level messages
	Dz1SyslogPri_max
} Dz1SyslogPri;

#define DZ1_SYSLOGR_PF_EMERG		(0x1 << Dz1SyslogPri_EMERG)
#define DZ1_SYSLOGR_PF_ALERT		(0x1 << Dz1SyslogPri_ALERT)
#define DZ1_SYSLOGR_PF_CRIT			(0x1 << Dz1SyslogPri_CRIT)
#define DZ1_SYSLOGR_PF_ERR			(0x1 << Dz1SyslogPri_ERR)
#define DZ1_SYSLOGR_PF_WARNING		(0x1 << Dz1SyslogPri_WARNING)
#define DZ1_SYSLOGR_PF_NOTICE		(0x1 << Dz1SyslogPri_NOTICE)
#define DZ1_SYSLOGR_PF_INFO			(0x1 << Dz1SyslogPri_INFO)
#define DZ1_SYSLOGR_PF_DEBUG		(0x1 << Dz1SyslogPri_DEBUG)
#define DZ1_SYSLOGR_PF_ALL			0xFF

// facility codes
#define	DZ1_SYSLOGR_F_KERN			(0<<3)		// kernel messages
#define	DZ1_SYSLOGR_F_USER			(1<<3)		// random user-level messages
#define	DZ1_SYSLOGR_F_MAIL			(2<<3)		// mail system
#define	DZ1_SYSLOGR_F_DAEMON		(3<<3)		// system daemons
#define	DZ1_SYSLOGR_F_AUTH			(4<<3)		// security/authorization messages
#define	DZ1_SYSLOGR_F_SYSLOG		(5<<3)		// messages generated internally by syslogd
#define	DZ1_SYSLOGR_F_LPR			(6<<3)		// line printer subsystem
#define	DZ1_SYSLOGR_F_NEWS			(7<<3)		// network news subsystem
#define	DZ1_SYSLOGR_F_UUCP			(8<<3)		// UUCP subsystem
#define	DZ1_SYSLOGR_F_CRON			(9<<3)		// clock daemon
#define	DZ1_SYSLOGR_F_AUTHPRIV		(10<<3)		// security/authorization messages (private)
#define	DZ1_SYSLOGR_F_FTP			(11<<3)		// ftp daemon

#define	DZ1_SYSLOGR_F_LOCAL0		(16<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL1		(17<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL2		(18<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL3		(19<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL4		(20<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL5		(21<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL6		(22<<3)		// reserved for local use
#define	DZ1_SYSLOGR_F_LOCAL7		(23<<3)		// reserved for local use

#define DZ1_SYSLOGR_SYSNAME_SIZE	255
#define DZ1_SYSLOGR_APPNAME_SIZE	48
#define DZ1_SYSLOGR_PID_SIZE		128
#define DZ1_SYSLOGR_BUF_SIZE		8192

typedef struct Dz1SyslogRA
{
	Dz1UdpSocket	*sock;
	Dz1SockAddr		 peer;
	Dz1SockAddr		 local;
	u32_t			 facilitiy;		// 0b11111000
	u32_t			 priority_flag;
	pthread_mutex_t	 lock;

	u8_t			 buf[DZ1_SYSLOGR_BUF_SIZE + 1];

	char			 str_pid[DZ1_SYSLOGR_PID_SIZE + 1];
	char			 sys_name[DZ1_SYSLOGR_SYSNAME_SIZE + 1];
	char			 app_name[DZ1_SYSLOGR_APPNAME_SIZE + 1];
} Dz1SyslogRA;

DZ1_CPPLINK Dz1SyslogRA *Dz1SyslogR_newA(char *url, u16_t port, u32_t DZ1_SYSLOGR_F, u32_t DZ1_SYSLOGR_PF, Dz1Error *err);
DZ1_CPPLINK void		 Dz1SyslogR_delA(Dz1SyslogRA *p);
static __inline__ void	 Dz1SyslogR_delAndSetNullA(void *pptr)
{
	Dz1SyslogRA **p = (Dz1SyslogRA **)pptr;
	Dz1SyslogR_delA(*p);
	*p = NULL;
}
DZ1_CPPLINK void		 Dz1SyslogR_dumpA(Dz1SyslogRA *p, int tab);

DZ1_CPPLINK char		*Dz1SyslogPriToStrA(Dz1SyslogPri v);
DZ1_CPPLINK Dz1SyslogPri Dz1SyslogPriFromStrA(char *str);

DZ1_CPPLINK bool_t		 Dz1SyslogR_vlogA(Dz1SyslogRA *dst, Dz1SyslogPri priority, char *fmt, va_list ap);
DZ1_CPPLINK bool_t		 Dz1SyslogR_logA(Dz1SyslogRA *dst, Dz1SyslogPri priority, char *fmt, ...);

#ifndef UNIX_SYSTEM
typedef struct Dz1SyslogRW
{
	Dz1UdpSocket	*sock;
	Dz1SockAddr		 peer;
	Dz1SockAddr		 local;
	u32_t			 facilitiy;
	u32_t			 priority_flag;
	pthread_mutex_t	 lock;

	u8_t			 buf[DZ1_SYSLOGR_BUF_SIZE + 1];

	wchar_t			 str_pid[DZ1_SYSLOGR_PID_SIZE + 1];
	wchar_t			 sys_name[DZ1_SYSLOGR_SYSNAME_SIZE + 1];
	wchar_t			 app_name[DZ1_SYSLOGR_APPNAME_SIZE + 1];
} Dz1SyslogRW;

DZ1_CPPLINK Dz1SyslogRW *Dz1SyslogR_newW(wchar_t *url, u16_t port, u32_t DZ1_SYSLOGR_F, u32_t DZ1_SYSLOGR_PF, Dz1Error *err);
DZ1_CPPLINK void		 Dz1SyslogR_delW(Dz1SyslogRW *p);
static __inline__ void	 Dz1SyslogR_delAndSetNullW(void *pptr)
{
	Dz1SyslogRW **p = (Dz1SyslogRW **)pptr;
	Dz1SyslogR_delW(*p);
	*p = NULL;
}
DZ1_CPPLINK void		 Dz1SyslogR_dumpW(Dz1SyslogRW *p, int tab);

DZ1_CPPLINK wchar_t		*Dz1SyslogPriToStrW(Dz1SyslogPri v);
DZ1_CPPLINK Dz1SyslogPri Dz1SyslogPriFromStrW(wchar_t *str);

DZ1_CPPLINK bool_t		 Dz1SyslogR_vlogW(Dz1SyslogRW *dst, Dz1SyslogPri priority, wchar_t *fmt, va_list ap);
DZ1_CPPLINK bool_t		 Dz1SyslogR_logW(Dz1SyslogRW *dst, Dz1SyslogPri priority, wchar_t *fmt, ...);

#ifdef	UNICODE
#define Dz1SyslogR					Dz1SyslogRW
#define Dz1SyslogR_new				Dz1SyslogR_newW
#define Dz1SyslogR_del				Dz1SyslogR_delW
#define Dz1SyslogR_delAndSetNull	Dz1SyslogR_delAndSetNullW
#define Dz1SyslogR_dump				Dz1SyslogR_dumpW
#define Dz1SyslogR_vlog				Dz1SyslogR_vlogW
#define Dz1SyslogR_log				Dz1SyslogR_logW
#define Dz1SyslogPriToStr			Dz1SyslogPriToStrW
#define Dz1SyslogPriFromStr			Dz1SyslogPriFromStrW
#else // UNICODE
#define Dz1SyslogR					Dz1SyslogRA
#define Dz1SyslogR_new				Dz1SyslogR_newA
#define Dz1SyslogR_del				Dz1SyslogR_delA
#define Dz1SyslogR_delAndSetNull	Dz1SyslogR_delAndSetNullA
#define Dz1SyslogR_dump				Dz1SyslogR_dumpA
#define Dz1SyslogR_vlog				Dz1SyslogR_vlogA
#define Dz1SyslogR_log				Dz1SyslogR_logA
#define Dz1SyslogPriToStr			Dz1SyslogPriToStrA
#define Dz1SyslogPriFromStr			Dz1SyslogPriFromStrA
#endif // UNICODE
#else // UNIX_SYSTEM
#define Dz1SyslogR					Dz1SyslogRA
#define Dz1SyslogR_new				Dz1SyslogR_newA
#define Dz1SyslogR_del				Dz1SyslogR_delA
#define Dz1SyslogR_delAndSetNull	Dz1SyslogR_delAndSetNullA
#define Dz1SyslogR_dump				Dz1SyslogR_dumpA
#define Dz1SyslogR_vlog				Dz1SyslogR_vlogA
#define Dz1SyslogR_log				Dz1SyslogR_logA
#define Dz1SyslogPriToStr			Dz1SyslogPriToStrA
#define Dz1SyslogPriFromStr			Dz1SyslogPriFromStrA
#endif // UNIX_SYSTEM

#endif

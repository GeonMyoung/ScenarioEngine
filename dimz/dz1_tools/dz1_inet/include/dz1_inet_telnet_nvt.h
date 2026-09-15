#ifndef DZ1_INET_TELNET_NVT_H
#define DZ1_INET_TELNET_NVT_H

#include <dz1_inet_telnet_msg.h>

typedef enum Dz1InetTelnetNVTPrinterEvent
{
	Dz1InetTelnetNVTPrinterEvent_bell = 7,
	Dz1InetTelnetNVTPrinterEvent_ec,	// backspace
	Dz1InetTelnetNVTPrinterEvent_htab,
	Dz1InetTelnetNVTPrinterEvent_lf,
	Dz1InetTelnetNVTPrinterEvent_vtab,
	Dz1InetTelnetNVTPrinterEvent_ff,
	Dz1InetTelnetNVTPrinterEvent_cr,

	Dz1InetTelnetNVTPrinterEvent_crlf = 256,	// as newline
	Dz1InetTelnetNVTPrinterEvent_el,
	Dz1InetTelnetNVTPrinterEvent_max
} Dz1InetTelnetNVTPrinterEvent;

typedef struct Dz1InetTelnetNVTPrinter
{
	u32_t		 width;
	u32_t		 height;
	// dataConsume callback is data processing function for "data"
	// in client, this callback used to print data
	// in server, this callback used to processing command which peer User typed
	void		 (*dataConsume)(void *ptr, u8_t *data, size_t size);
	void		 (*event)(void *ptr, Dz1InetTelnetNVTPrinterEvent event);
} Dz1InetTelnetNVTPrinter;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTPrinter *Dz1InetTelnetNVTPrinter_new(u32_t width, u32_t height,
																			void (*dataConsume)(void *ptr, u8_t *data, size_t size),
																			void (*event)(void *ptr, Dz1InetTelnetNVTPrinterEvent event),
																			Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTPrinter_del(Dz1InetTelnetNVTPrinter *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTPrinter_dump(Dz1InetTelnetNVTPrinter *p, int tab);
static __inline__ void Dz1InetTelnetNVTPrinter_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTPrinter **p = (Dz1InetTelnetNVTPrinter **)ptr;
	Dz1InetTelnetNVTPrinter_del(*p); *p = NULL;
}

struct Dz1InetTelnetNVT;
typedef struct Dz1InetTelnetNVTKeyboard
{
	ssize_t (*write)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p, u8_t data, size_t size);
	Dz1Error (*brk)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
	Dz1Error (*intProc)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
	Dz1Error (*abortOutput)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
	Dz1Error (*eraseChar)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
	Dz1Error (*eraseLine)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
	Dz1Error (*goAhead)(struct Dz1InetTelnetNVT *env, struct Dz1InetTelnetNVTKeyboard *p);
} Dz1InetTelnetNVTKeyboard;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTKeyboard *Dz1InetTelnetNVTKeyboard_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTKeyboard_del(Dz1InetTelnetNVTKeyboard *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTKeyboard_dump(Dz1InetTelnetNVTKeyboard *p, int tab);
static __inline__ void Dz1InetTelnetNVTKeyboard_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTKeyboard **p = (Dz1InetTelnetNVTKeyboard **)ptr;
	Dz1InetTelnetNVTKeyboard_del(*p); *p = NULL;
}

typedef struct Dz1InetTelnetNVTOptValue
{
	bool_t						 value;
	bool_t						 waitReply;
} Dz1InetTelnetNVTOptValue;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOptValue *Dz1InetTelnetNVTOptValue_new(bool_t value, bool_t waitReply, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOptValue *Dz1InetTelnetNVTOptValue_clone(Dz1InetTelnetNVTOptValue *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOptValue_del(Dz1InetTelnetNVTOptValue *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOptValue_dump(Dz1InetTelnetNVTOptValue *p, int tab);
static __inline__ void Dz1InetTelnetNVTOptValue_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTOptValue **p = (Dz1InetTelnetNVTOptValue **)ptr;
	Dz1InetTelnetNVTOptValue_del(*p); *p = NULL;
}

typedef struct Dz1InetTelnetNVTOptEntry
{
	Dz1InetTelnetNVTOptValue	*peer;
	Dz1InetTelnetNVTOptValue	*local;
} Dz1InetTelnetNVTOptEntry;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOptEntry *Dz1InetTelnetNVTOptEntry_new(Dz1InetTelnetNVTOptValue *peer, Dz1InetTelnetNVTOptValue *local, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOptEntry *Dz1InetTelnetNVTOptEntry_clone(Dz1InetTelnetNVTOptEntry *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOptEntry_del(Dz1InetTelnetNVTOptEntry *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOptEntry_dump(Dz1InetTelnetNVTOptEntry *p, int tab);
static __inline__ void Dz1InetTelnetNVTOptEntry_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTOptEntry **p = (Dz1InetTelnetNVTOptEntry **)ptr;
	Dz1InetTelnetNVTOptEntry_del(*p); *p = NULL;
}

typedef bool_t (*Dz1InetTelnetNVTOptSetInform)(struct Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val);
typedef void (*Dz1InetTelnetNVTOptRepliedInform)(struct Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, bool_t val, Dz1InetTelnetNVTOptEntry *e);
typedef void (*Dz1InetTelnetNVTOptSubNego)(struct Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOpt *subNego);
typedef struct Dz1InetTelnetNVTOpt
{
	Dz1InetTelnetOptPresent				 present;
	Dz1InetTelnetNVTOptEntry			*status;

	Dz1InetTelnetNVTOptSetInform		 setPeerOpt;
	Dz1InetTelnetNVTOptRepliedInform	 repliedPeerOpt;

	Dz1InetTelnetNVTOptSetInform		 setLocalOpt;
	Dz1InetTelnetNVTOptRepliedInform	 repliedLocalOpt;

	Dz1InetTelnetNVTOptSubNego			 subNego;
} Dz1InetTelnetNVTOpt;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOpt *Dz1InetTelnetNVTOpt_new(Dz1InetTelnetOptPresent present, Dz1InetTelnetNVTOptEntry *defVal, 
																	 Dz1InetTelnetNVTOptSetInform setPeerOpt, Dz1InetTelnetNVTOptRepliedInform repliedPeerOpt,
																	 Dz1InetTelnetNVTOptSetInform setLocalOpt, Dz1InetTelnetNVTOptRepliedInform repliedLocalOpt,
																	 Dz1InetTelnetNVTOptSubNego subNego, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTOpt *Dz1InetTelnetNVTOpt_clone(Dz1InetTelnetNVTOpt *src, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOpt_del(Dz1InetTelnetNVTOpt *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTOpt_dump(Dz1InetTelnetNVTOpt *p, int tab);
static __inline__ void Dz1InetTelnetNVTOpt_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTOpt **p = (Dz1InetTelnetNVTOpt **)ptr;
	Dz1InetTelnetNVTOpt_del(*p); *p = NULL;
}

typedef struct Dz1InetTelnetNVTControl
{
	Dz1InetTelnetNVTOpt			**opts;
	u32_t						 numOfOpts;
} Dz1InetTelnetNVTControl;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVTControl *Dz1InetTelnetNVTControl_new(Dz1InetTelnetNVTOpt *opts, u32_t numOfOpts, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTControl_del(Dz1InetTelnetNVTControl *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVTControl_dump(Dz1InetTelnetNVTControl *p, int tab);
static __inline__ void Dz1InetTelnetNVTControl_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVTControl **p = (Dz1InetTelnetNVTControl **)ptr;
	Dz1InetTelnetNVTControl_del(*p); *p = NULL;
}

typedef struct Dz1InetTelnetNVT
{
	Dz1InetTelnetNVTPrinter		*printer;
	Dz1InetTelnetNVTKeyboard	*keyboard;
	Dz1InetTelnetNVTControl		*control;
	void						*userResource;
	Dz1DelFunc					 userResourceDel;
} Dz1InetTelnetNVT;

DZ1_CPPLINK DZ1_DLLPORT Dz1InetTelnetNVT *Dz1InetTelnetNVT_new(u32_t width, u32_t height,
															   void (*dataConsume)(void *ptr, u8_t *data, size_t size),
															   void (*event)(void *ptr, Dz1InetTelnetNVTPrinterEvent event),
															   Dz1InetTelnetNVTOpt *opts, u32_t numOfOpts,
															   void *userResource, Dz1DelFunc userResourceDel,
															   Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVT_del(Dz1InetTelnetNVT *p);
DZ1_CPPLINK DZ1_DLLPORT void Dz1InetTelnetNVT_dump(Dz1InetTelnetNVT *p, int tab);
static __inline__ void Dz1InetTelnetNVT_delAndSetNull(void *ptr)
{
	Dz1InetTelnetNVT **p = (Dz1InetTelnetNVT **)ptr;
	Dz1InetTelnetNVT_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1InetTelnetNVT_recv(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetMsg *msg);

DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1InetTelnetNVT_optSetLocal(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOptPresent opt, bool_t value);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error Dz1InetTelnetNVT_optSetPeer(Dz1InetTelnetNVT *env, Dz1TcpClientSocket *s, Dz1InetTelnetOptPresent opt, bool_t value);

#endif

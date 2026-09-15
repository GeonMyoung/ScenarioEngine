#ifndef DZ1_SOCKET_BUF_H
#define DZ1_SOCKET_BUF_H

#include <dz1_error.h>

typedef struct Dz1SocketBuffer
{
	u8_t *buf;
	size_t size;
	size_t push;
	size_t pop;
} Dz1SocketBuffer;
typedef Dz1SocketBuffer	Dz1SocketBuf;

DZ1_CPPLINK DZ1_DLLPORT Dz1SocketBuf	*Dz1SocketBuf_new(size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketBuf_del(Dz1SocketBuf *ptr);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketBufA_dump(Dz1SocketBuf *ptr, int tab);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketBufW_dump(Dz1SocketBuf *ptr, int tab);
#ifdef UNICODE
#define									 Dz1SocketBuf_dump		Dz1SocketBufW_dump
#else // UNICODE
#define									 Dz1SocketBuf_dump		Dz1SocketBufA_dump
#endif // UNICODE
#else // UNIX_SYSTEM
#define									 Dz1SocketBuf_dump		Dz1SocketBufA_dump
#endif // UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1SocketBuf	*Dz1SocketBuf_clone(Dz1SocketBuf *ptr, Dz1Error *err);
static __inline__ void					 Dz1SocketBuf_delAndSetNull(void *ptr)
{
	Dz1SocketBuf **p = (Dz1SocketBuf **)ptr;
	Dz1SocketBuf_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1SocketBuf_push(Dz1SocketBuf *ptr, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1SocketBuf_pop(Dz1SocketBuf *ptr, u8_t *buf, size_t size, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketBuf_fit(Dz1SocketBuf *ptr);
DZ1_CPPLINK DZ1_DLLPORT void			 Dz1SocketBuf_flush(Dz1SocketBuf *ptr);
DZ1_CPPLINK DZ1_DLLPORT u8_t			*Dz1SocketBuf_getData(Dz1SocketBuf *ptr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT ssize_t			 Dz1SocketBuf_getSize(Dz1SocketBuf *ptr, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT size_t			 Dz1SocketBuf_getBufSize(Dz1SocketBuf *ptr);
DZ1_CPPLINK DZ1_DLLPORT Dz1Error		 Dz1SocketBuf_expand(Dz1SocketBuf *ptr, size_t size);
#endif


#ifndef DZ1_SOCKET_FIFO_H_LOCAL
#define DZ1_SOCKET_FIFO_H_LOCAL

#include <dz1_socket_fifo.h>

///////////////////////////////////////////////////////////////////////////////
// TX FIFO Type 2 : Byte CODEC mode(deprecated)
typedef struct Dz1SocketMsgAPI
{
	Dz1EncodeFunc	 enc;
	void			*enc_param;

	Dz1DelFunc		 del;
	Dz1DumpFunc		 dump;
} Dz1SocketMsgAPI;

typedef struct Dz1SocketFifo2Entry
{
	void				*msg;
	Dz1Binary			*stream;
	Dz1SocketMsgAPI		*api;
	bool_t				 verbose;
} Dz1SocketFifo2Entry;

typedef struct _Dz1SocketFifo2
{
	Dz1SocketMsgAPI		 api;
	Dz1Fifo				*fifo;
	bool_t				 verbose;
} _Dz1SocketFifo2;
// TX FIFO Type 2 : Byte CODEC mode(deprecated)
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// TX FIFO Type 3 : Universal Mode
typedef struct Dz1SocketFifo3API
{
	Dz1SocketFifo3Encoder	 msg_enc;
	Dz1CloneFunc			 msg_clone;
	Dz1DelFunc				 msg_del;
	Dz1DumpFunc				 msg_dump;

	void					*param;
	Dz1DelFunc				 param_del;
} Dz1SocketFifo3API;
DZ1_CPPLINK Dz1SocketFifo3API *Dz1SocketFifo3API_new(Dz1SocketFifo3Encoder msg_enc,
													 Dz1CloneFunc msg_clone, Dz1DelFunc msg_del, Dz1DumpFunc msg_dump,
													 void *param, Dz1DelFunc param_del, Dz1Error *err);
DZ1_CPPLINK Dz1SocketFifo3API *Dz1SocketFifo3API_clone(Dz1SocketFifo3API *src, Dz1Error *err);
DZ1_CPPLINK void Dz1SocketFifo3API_del(Dz1SocketFifo3API *p);
static __inline__ void Dz1SocketFifo3API_delAndSetNull(void *pptr)
{
	Dz1SocketFifo3API **p = (Dz1SocketFifo3API **)pptr;
	Dz1SocketFifo3API_del(*p); *p = NULL;
}

DZ1_CPPLINK void Dz1SocketFifo3API_dump(Dz1SocketFifo3API *p, int tab);

typedef struct Dz1SocketFifo3Entry
{
	void					*msg;
	Dz1SocketFifo3API		*api;				// is ref

	bool_t					 verbose;			// entry verbose
} Dz1SocketFifo3Entry;
DZ1_CPPLINK Dz1SocketFifo3Entry *Dz1SocketFifo3Entry_new(void *msg, Dz1SocketFifo3API *api, bool_t verbose, Dz1Error *err);
DZ1_CPPLINK void Dz1SocketFifo3Entry_del(Dz1SocketFifo3Entry *p);
static __inline__ void Dz1SocketFifo3Entry_delAndSetNull(void *ptr)
{
	Dz1SocketFifo3Entry **p = (Dz1SocketFifo3Entry **)ptr;
	Dz1SocketFifo3Entry_del(*p); *p = NULL;
}

DZ1_CPPLINK void Dz1SocketFifo3Entry_dump(Dz1SocketFifo3Entry *p, int tab);

typedef struct _Dz1SocketFifo3
{
	bool_t				 wait_sent;

	Dz1Fifo				*fifo;
	Dz1SocketFifo3API	*api;

	Dz1ElasticBuf		*tx_buf;
	Dz1Stream			*encode_dst;

	bool_t				 verbose;				// common verbose
} _Dz1SocketFifo3;
// TX FIFO Type 3 : Universal Mode
///////////////////////////////////////////////////////////////////////////////


#endif
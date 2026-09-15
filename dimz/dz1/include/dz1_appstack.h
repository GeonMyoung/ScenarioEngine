#ifndef DZ1_APPSTACK_H
#define DZ1_APPSTACK_H

#include <dz1_sync.h>
#include <dz1_socket.h>

///////////////////////////////////////////////////////////////////////////////
// !! Work in Progress !!
// Do Not Use This APIs
///////////////////////////////////////////////////////////////////////////////

struct Dz1AppStackEntry;

typedef Dz1Error (*Dz1AppStackEntryBackwardFunc)(void *userPtr,  u8_t *data, size_t size);
typedef void (*Dz1AppStackEntryExceptiondFunc)(void *userPtr,  struct Dz1AppStackEntry *p, Dz1Error *reason);

typedef struct Dz1AppStackEntry
{
	void *priv;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// User or Higher Layer API
	ssize_t (*forward)(struct Dz1AppStackEntry *p, u8_t *data, size_t size, Dz1Sync *sync, Dz1Error *err);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Current Layer API
	Dz1AppStackEntryBackwardFunc b;
	Dz1AppStackEntryExceptiondFunc e;
	void *userPtr;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	Dz1Error (*setup)(struct Dz1AppStackEntry *p,
							Dz1AppStackEntryBackwardFunc b,
							Dz1AppStackEntryExceptiondFunc e,
							void *userPtr);
} Dz1AppStackEntry;
DZ1_CPPLINK DZ1_DLLPORT Dz1AppStackEntry *Dz1AppStackEntry_new(
									ssize_t (*forward)(struct Dz1AppStackEntry *p, u8_t *data, size_t size, Dz1Sync *sync, Dz1Error *err),
									Dz1Error *err);

typedef struct Dz1AppProtocol
{
	str_t name;
	void *priv;
	Dz1AppStackEntry *associate;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// User or Higher Layer API
	Dz1AppStackEntry *(*open)(struct Dz1AppProtocol *p, void *opt,
								Dz1AppStackEntryBackwardFunc b, Dz1AppStackEntryExceptiondFunc e,
								void *userPtr, Dz1Error *err);
	void (*close)(struct Dz1AppProtocol *p, Dz1AppStackEntry *e);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Lower Layer API
	Dz1Error (*initiate)(struct Dz1AppProtocol *p);
	Dz1Error (*backward)(struct Dz1AppProtocol *p, u8_t *buf, size_t size);
	void (*exception)(struct Dz1AppProtocol *p, Dz1Error *reason);
	Dz1CancelFunc cleanup;
} Dz1AppProtocol;

DZ1_CPPLINK DZ1_DLLPORT Dz1AppProtocol *Dz1AppStackTcpClientSubsystem_new(Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1AppStackTcpSubsystem_del(Dz1AppProtocol *p);
static __inline__ void Dz1AppStackTcpClientSubsystem_delAndSetNull(void *ptr)
{
	Dz1AppProtocol **p = (Dz1AppProtocol **)ptr;
	Dz1AppStackTcpSubsystem_del(*p); *p = NULL;
}

#endif

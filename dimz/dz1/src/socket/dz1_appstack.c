#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_appstack.h>

static Dz1Error Dz1AppStackEntry_setup(Dz1AppStackEntry *p,
										Dz1AppStackEntryBackwardFunc b,
										Dz1AppStackEntryExceptiondFunc e,
										void *userPtr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->b) { ERR_SET_OUT(&err, EEXIST); }
	else
	{
		p->b = b;
		p->e = e;
		p->userPtr = userPtr;
	}
	return err;
}

Dz1AppStackEntry *Dz1AppStackEntry_new(ssize_t (*forward)(struct Dz1AppStackEntry *p, u8_t *data, size_t size, Dz1Sync *sync, Dz1Error *err), Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1AppStackEntry *ret = (Dz1AppStackEntry *)Dz1Calloc(sizeof(Dz1AppStackEntry), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		ret->forward = forward;
		ret->setup = Dz1AppStackEntry_setup;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

typedef struct Dz1AppStackTcpClientSubsystemEntryPriv
{
	u32_t tx;
	u32_t rx;
} Dz1AppStackTcpClientSubsystemEntryPriv;

static void Dz1AppStackTcpClientSubsystemEntryPriv_del(Dz1AppStackTcpClientSubsystemEntryPriv *p)
{
	if (!p) return;
	Dz1Free(p);
}

ssize_t Dz1AppStackTcpClientSubsystemEntry_forward(Dz1AppStackEntry *p, u8_t *data, size_t size, Dz1Sync *sync, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1AppStackTcpClientSubsystemEntryPriv *priv = (Dz1AppStackTcpClientSubsystemEntryPriv *)p->priv;
	if (priv == NULL) { ERR_SET_OUT(errp, EAGAIN); }
	else
	{
		// DZ1XXX : Create TX Message and post
	}
	return ret;
}

static void Dz1AppStackTcpClientSubsystemEntry_cleanup(Dz1AppStackEntry *p)
{
	if (p->priv) Dz1AppStackTcpClientSubsystemEntryPriv_del((Dz1AppStackTcpClientSubsystemEntryPriv *)p->priv);
	p->priv = NULL;
}

typedef struct Dz1AppStackTcpClientSubsystemPriv
{
	bool_t referenced;
} Dz1AppStackTcpClientSubsystemPriv;

static Dz1AppStackTcpClientSubsystemPriv *Dz1AppStackTcpClientSubsystemPriv_new(Dz1Error *errp)
{
	Dz1AppStackTcpClientSubsystemPriv *ret = (Dz1AppStackTcpClientSubsystemPriv *)Dz1Calloc(sizeof(Dz1AppStackTcpClientSubsystemPriv), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	return ret;
}

static void Dz1AppStackTcpClientSubsystemPriv_del(Dz1AppStackTcpClientSubsystemPriv *p)
{
	if (!p) return;
	Dz1Free(p);
}

static Dz1AppStackEntry *Dz1AppStackTcpClientSubsystem_open(Dz1AppProtocol *p, void *opt,
															Dz1AppStackEntryBackwardFunc b,
															Dz1AppStackEntryExceptiondFunc e,
															void *userPtr, Dz1Error *err)
{
	Dz1AppStackEntry *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1AppStackTcpClientSubsystemPriv *priv = (Dz1AppStackTcpClientSubsystemPriv *)p->priv;

	if (priv->referenced) { ERR_SET_OUT(errp, EEXIST); }
	else if ((*errp = p->associate->setup(p->associate, b, e, userPtr)).code) { ERR_OUT(errp); }
	else
	{
		ret = p->associate;
		priv->referenced = TRUE;
		Dz1Error_set(errp, 0);
	}

	return ret;
}

static void Dz1AppStackTcpClientSubsystem_close(Dz1AppProtocol *p, Dz1AppStackEntry *e)
{
	if (p->associate == e)
	{
		Dz1AppStackTcpClientSubsystemPriv *priv = (Dz1AppStackTcpClientSubsystemPriv *)p->priv;
		priv->referenced = FALSE;
		p->associate->setup(p->associate, NULL, NULL, NULL);
	}
}

static Dz1Error Dz1AppStackTcpClientSubsystem_initiate(Dz1AppProtocol *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	return err;
}

static Dz1Error Dz1AppStackTcpClientSubsystem_backward(Dz1AppProtocol *p, u8_t *data, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (p->associate->b)
	{
		if ((err = p->associate->b(p->associate->userPtr, data, size)).code) { ERR_OUT(&err); }
	}
	return err;
}

static void Dz1AppStackTcpClientSubsystem_exception(Dz1AppProtocol *p, Dz1Error *reason)
{
	if (p->associate->e)
		p->associate->e(p->associate->userPtr, p->associate, reason);
}

static void Dz1AppStackTcpClientSubsystem_cleanup(void *ptr)
{
	Dz1AppProtocol *p = (Dz1AppProtocol *)ptr;
	Dz1AppStackTcpClientSubsystemEntry_cleanup(p->associate);
	if (p->priv) { Dz1AppStackTcpClientSubsystemPriv_del(p->priv); p->priv = NULL; }
}

Dz1AppProtocol *Dz1AppStackTcpClientSubsystem_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1AppProtocol *ret = (Dz1AppProtocol *)Dz1Calloc(sizeof(Dz1AppProtocol), 1, errp);
	if (ret == NULL) { ERR_OUT(errp); }
	else
	{
		pthread_cleanup_push(Dz1AppStackTcpClientSubsystem_delAndSetNull, (void *)&ret);

		if ((ret->name = Dz1StrA_dup("Dz1TcpSocketSubSystem", errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->priv = Dz1AppStackTcpClientSubsystemPriv_new(errp)) == NULL) { ERR_OUT(errp); }
		else if ((ret->associate = Dz1AppStackEntry_new(Dz1AppStackTcpClientSubsystemEntry_forward, errp)) == NULL) { ERR_OUT(errp); }
		else
		{
			ret->open = Dz1AppStackTcpClientSubsystem_open;
			ret->close = Dz1AppStackTcpClientSubsystem_close;
			ret->initiate = Dz1AppStackTcpClientSubsystem_initiate;
			ret->backward = Dz1AppStackTcpClientSubsystem_backward;
			ret->exception = Dz1AppStackTcpClientSubsystem_exception;
			ret->cleanup = Dz1AppStackTcpClientSubsystem_cleanup;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1AppStackTcpClientSubsystem_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1AppProtocol *Dz1AppStackTcpServerSubsystem_new(Dz1SockAddr *local, Dz1Error *err);

void Dz1AppStackTcpSubsystem_del(Dz1AppProtocol *p);


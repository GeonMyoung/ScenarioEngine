#include <dz1_malloc.h>
#include <dz1_thread_stdio.h>
#include <dz1_socket_buf.h>

Dz1SocketBuf *Dz1SocketBuf_new(size_t size, Dz1Error *err)
{
	Dz1SocketBuffer *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (size == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SocketBuffer *)Dz1Calloc(sizeof(Dz1SocketBuffer), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SocketBuf_delAndSetNull, (void *)&ret);
		if ((ret->buf = (u8_t *)Dz1Malloc(size, errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->size = size;
			ret->push = 0;
			ret->pop = 0;
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(errp->code); // (Dz1SocketBuf_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1SocketBuf_del(Dz1SocketBuf *ptr)
{
	Dz1SocketBuffer *p = (Dz1SocketBuffer *)ptr;
	if (p == NULL) return;
	if (p->buf) Dz1Free(p->buf);
	Dz1Free(p);
}

void Dz1SocketBufA_dump(Dz1SocketBuf *ptr, int tab)
{
	Dz1SocketBuffer *p = (Dz1SocketBuffer *)ptr;
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else 
	{
		size_t dsz = p->push < p->pop ? ~p->push + p->pop : p->push - p->pop;
		Dz1ThreadA_printf("%u/%u\n", dsz, p->size);
	}
}
#ifndef UNIX_SYSTEM
void Dz1SocketBufW_dump(Dz1SocketBuf *ptr, int tab)
{
	Dz1SocketBuffer *p = (Dz1SocketBuffer *)ptr;
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else 
	{
		size_t dsz = p->push < p->pop ? ~p->push + p->pop : p->push - p->pop;
		Dz1ThreadW_printf(L"%u/%u\n", dsz, p->size);
	}
}
#endif
Dz1SocketBuf *Dz1SocketBuf_clone(Dz1SocketBuf *ptr, Dz1Error *err)
{
	Dz1SocketBuffer *ret = NULL, *src = (Dz1SocketBuffer *)ptr;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1SocketBuffer *)Dz1SocketBuf_new(src->size, errp)) == NULL) ERR_OUT(errp);
	else
	{
		memcpy(ret->buf, src->buf, src->size);
		ret->push = src->push;
		ret->pop = src->pop;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

ssize_t Dz1SocketBuf_push(Dz1SocketBuf *ptr, u8_t *data, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	if (dst == NULL || data == NULL || size == 0) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else
	{
		size_t spaceSize = dst->size - dst->push;
		size_t copySize = size < spaceSize ? size : spaceSize;
		memcpy(&dst->buf[dst->push], data, copySize);
		dst->push += copySize;
		ret = (ssize_t)copySize;
	}
	return ret;
}

ssize_t Dz1SocketBuf_pop(Dz1SocketBuf *ptr, u8_t *buf, size_t size, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	if (dst == NULL || size == 0) { ERR_SET_OUT(errp, EINVAL); ret = -1; }
	else
	{
		size_t dataSize = dst->push - dst->pop;
		size_t copySize = size < dataSize ? size : dataSize;
		if (buf != NULL) memcpy(buf, &dst->buf[dst->pop], copySize);
		dst->pop += copySize;
		ret = (ssize_t)copySize;
	}
	return ret;
}

Dz1Error Dz1SocketBuf_fit(Dz1SocketBuf *ptr)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	if (dst == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (dst->pop != 0)
	{
		size_t dataSize = dst->push - dst->pop;
		if (dataSize) memcpy(dst->buf, &dst->buf[dst->pop], dataSize);
		dst->pop = 0;
		dst->push = dataSize;
	}
	return err;
}

void Dz1SocketBuf_flush(Dz1SocketBuf *ptr)
{
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	if (dst != NULL) dst->push = dst->pop = 0;
}

u8_t *Dz1SocketBuf_getData(Dz1SocketBuf *ptr, Dz1Error *err)
{
	u8_t *ret = NULL;
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else ret = &dst->buf[dst->pop];
	return ret;
}

ssize_t Dz1SocketBuf_getSize(Dz1SocketBuf *ptr, Dz1Error *err)
{
	ssize_t ret = -1;
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else ret = (ssize_t)(dst->push - dst->pop);
	return ret;
}

Dz1Error Dz1SocketBuf_expand(Dz1SocketBuf *ptr, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SocketBuffer *dst = (Dz1SocketBuffer *)ptr;

	if (dst->size < size)
	{
		u8_t *mem = dst->buf;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&mem);
		if ((dst->buf = (u8_t *)Dz1Malloc(size, &err)) == NULL) ERR_OUT(&err);
		else
		{
			memcpy(dst->buf, mem, dst->size);
			dst->size = size;
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&mem);
	}

	return err;
}

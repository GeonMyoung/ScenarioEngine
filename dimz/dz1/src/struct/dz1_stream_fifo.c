#include <dz1_sync.h>
#include <dz1_malloc.h>
#include <dz1_stream_fifo.h>
 
typedef enum Dz1StreamFifoState
{
	Dz1StreamFifoState_empty,
	Dz1StreamFifoState_filled,
	Dz1StreamFifoState_full
} Dz1StreamFifoState;

typedef struct _Dz1StreamFifo
{
	u8_t				*buffer;
	size_t				 size;
	size_t				 head;
	size_t				 tail;
	Dz1StreamFifoState	 state;
} _Dz1StreamFifo;

static ssize_t _getDataSize(_Dz1StreamFifo *p, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ssize_t ret = -1;
	if (p->tail < p->head)
	{
		ret = (ssize_t)(p->head - p->tail);
	}
	else if (p->head < p->tail)
	{
		ret = (ssize_t)(p->size - p->tail + p->head);
	}
	else // (p->head == p->tail)
	{
		switch(p->state)
		{
		case Dz1StreamFifoState_empty:
			ret = 0;
			break;
		case Dz1StreamFifoState_full:
			ret = (ssize_t)p->size;
			break;
		default:
		case Dz1StreamFifoState_filled:
			ERR_SET_OUT(errp, EINVAL);
			ret = -1;
			break;
		}
	}
	return ret;
}

static ssize_t _getSpaceSize(_Dz1StreamFifo *p, Dz1Error *errp)
{
	ssize_t ret = _getDataSize(p, errp);
	if (ret < 0) ERR_OUT(errp); else ret = (ssize_t)(p->size - ret);
	return ret;
}

void *Dz1StreamFifo_new(size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	_Dz1StreamFifo *ret = (_Dz1StreamFifo *)Dz1Calloc(sizeof(_Dz1StreamFifo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StreamFifo_delAndSetNull, (void *)&ret);
		if ((ret->buffer = (u8_t *)Dz1Malloc((ret->size = size), errp)) == NULL) ERR_OUT(errp);
		else
		{
			ret->head = ret->tail = 0;
			ret->state = Dz1StreamFifoState_empty;
		}
		pthread_cleanup_pop(errp->code); // (Dz1StreamFifo_delAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1StreamFifo_del(void *ptr)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	if (p == NULL) return;
	if (p->buffer) { Dz1Free(p->buffer); p->buffer = NULL; } // modified by gm 20230601
	Dz1Free(p);
}

void Dz1StreamFifo_delAndSetNull(void *ptr)
{
	_Dz1StreamFifo **p = (_Dz1StreamFifo **)ptr;
	Dz1StreamFifo_del(*p); *p = NULL;
}

void Dz1StreamFifoA_dump(void *ptr, int tab)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	if (!p) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("[%d/%u]\n", _getDataSize(p, NULL), p->size);
}
#ifndef UNIX_SYSTEM
void Dz1StreamFifoW_dump(void *ptr, int tab)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"[%d/%u]\n", _getDataSize(p, NULL), p->size);
}
#endif
static void _fixFlag(_Dz1StreamFifo *p, Dz1StreamFifoState state)
{
	if (p->head == p->tail) p->state = state;
	else p->state = Dz1StreamFifoState_filled;
}

bool_t Dz1StreamFifo_isFull(Dz1StreamFifo *ptr)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	bool_t ret = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t status = _getSpaceSize(p, &err);

	if (status < 0) ERR_OUT(&err);
	else if (status == 0) ret = TRUE;
	else ret = FALSE;

	return ret;
}

bool_t Dz1StreamFifo_isEmpty(Dz1StreamFifo *ptr)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	bool_t ret = -1;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ssize_t status = _getDataSize(p, &err);

	if (status < 0) ERR_OUT(&err);
	else if (status == 0) ret = TRUE;
	else ret = FALSE;

	return ret;
}

ssize_t Dz1StreamFifo_push(Dz1StreamFifo *ptr, u8_t *data, size_t size, Dz1Error *err)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t spaceSize = 0;

	Dz1Error_set(errp, 0);
	if ((spaceSize = _getSpaceSize(p, errp)) < 0) ERR_OUT(errp);
	else if (spaceSize == 0) return 0;
	else
	{
		size_t continuousSize = p->size - p->head;
		ret = spaceSize < (ssize_t)size ? spaceSize : (ssize_t)size;
		if (ret > (ssize_t)continuousSize)
		{
			size_t rearSize = ret - continuousSize;
			u8_t *cp = data;
			memcpy(&p->buffer[p->head], cp, continuousSize);
			cp += continuousSize;
			memcpy(p->buffer, cp, rearSize);
			p->head = rearSize;
		}
		else
		{
			memcpy(&p->buffer[p->head], data, ret);
			p->head += ret;
		}
		_fixFlag(p, Dz1StreamFifoState_full);
	}
	return ret;
}

ssize_t Dz1StreamFifo_pop(Dz1StreamFifo *ptr, u8_t *buf, size_t size, Dz1Error *err)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t dataSize = 0;

	Dz1Error_set(errp, 0);
	if ((dataSize = _getDataSize(p, errp)) < 0) ERR_OUT(errp);
	else if (dataSize == 0) return 0;
	else
	{
		size_t continuousSize = p->size - p->tail;

		ret = dataSize < (ssize_t)size ? dataSize : (ssize_t)size;

		if (ret > (ssize_t)continuousSize)
		{
			size_t rearSize = ret - continuousSize;
			u8_t *dp = buf;
			memcpy(dp, &p->buffer[p->tail], continuousSize);
			dp += continuousSize;
			memcpy(dp, p->buffer, rearSize);
			p->tail = rearSize;
		}
		else
		{
			memcpy(buf, &p->buffer[p->tail], ret);
			p->tail += ret;
		}
		_fixFlag(p, Dz1StreamFifoState_empty);
	}
	return ret;
}

ssize_t Dz1StreamFifo_getDataSize(Dz1StreamFifo *ptr, Dz1Error *err)
{
	_Dz1StreamFifo *p = (_Dz1StreamFifo *)ptr;
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((ret = _getDataSize(p, errp)) < 0) ERR_OUT(errp);
	return ret;
}

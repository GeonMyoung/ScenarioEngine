#include <errno.h>
#include <pthread.h>
#include <sys/time.h>

#include "hae_local_memory.h"

#include "hae_output.h"

#include "hae_local_liner_buf.h"

static void mutex_unlock(void *p) { pthread_mutex_unlock((pthread_mutex_t *)p); }

static int haeLocalLinerBuf_getFreeSize(HaeLocalLinerBuf *buf)
{
	switch(buf->status)
	{
		case HAE_LINER_BUF_EMPTY:
			return buf->size;
		case HAE_LINER_BUF_FULL:
			return 0;
		case HAE_LINER_BUF_FILLED:
		default:
			{
				int ret = 0;
				if (buf->head < buf->tail)
					ret = buf->tail - buf->head;
				else
					ret = (buf->size - buf->head) + buf->tail;
				return ret;
			}
			break;
	}
}

static int haeLocalLinerBuf_getDataSize(HaeLocalLinerBuf *buf)
{
	return buf->size - haeLocalLinerBuf_getFreeSize(buf);
}

static int haeLocalLinerBuf_push(HaeLocalLinerBuf *buf, u8_t *data, int size)
{
	int buf_size = 0, partial_size;
	pthread_mutex_lock(&buf->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&buf->lock);
	if (buf->status != HAE_LINER_BUF_FULL)
	{
		// Size Fix
		if ((buf_size = haeLocalLinerBuf_getFreeSize(buf)) < size) size = buf_size;
		buf_size = size;
		
		if ((partial_size = buf->size - buf->head) < size)
		{
			memcpy(&buf->buf[buf->head], data, partial_size);
			size -= partial_size;
			data += partial_size;
			memcpy(buf->buf, data, size);
			buf->head = size;
		}
		else
		{
			memcpy(&buf->buf[buf->head], data, size);
			buf->head += size;
		}

		if (buf->head == buf->tail) buf->status = HAE_LINER_BUF_FULL; else buf->status = HAE_LINER_BUF_FILLED;
		pthread_cond_signal(&buf->cond);
	}
	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&buf->lock);
	return buf_size;
}

static int haeLocalLinerBuf_popWait(HaeLocalLinerBuf *buf, struct timeval *to)
{
	int err = 0, data_size;
	pthread_mutex_lock(&buf->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&buf->lock);

	while((data_size = haeLocalLinerBuf_getDataSize(buf))==0 && buf->flag == HAE_LINER_BUF_INPUT_NORMAL)
		if (to)
		{
			struct timeval tNow;
			struct timespec tExpire;
			gettimeofday(&tNow, NULL);
			tExpire.tv_nsec = ((tNow.tv_usec + to->tv_usec) % 1000000) * 1000;
			tExpire.tv_sec = tNow.tv_sec + ((tNow.tv_usec + to->tv_usec) / 1000000);
			err = pthread_cond_timedwait(&buf->cond, &buf->lock, &tExpire);
		}
		else
			err = pthread_cond_wait(&buf->cond, &buf->lock);

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&buf->lock);

	return err;
}

static int haeLocalLinerBuf_pop(HaeLocalLinerBuf *buf, u8_t *data, int size)
{
	int data_size = 0;
	pthread_mutex_lock(&buf->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&buf->lock);

	// wait data
	while((data_size = haeLocalLinerBuf_getDataSize(buf))==0 && buf->flag == HAE_LINER_BUF_INPUT_NORMAL)
		pthread_cond_wait(&buf->cond, &buf->lock);

	if (data_size)
	{
		int partial_size = 0;

		// Size Fix
		if (data_size > size) data_size = size;
		size = data_size;
		if ((partial_size = buf->size - buf->tail) < size)
		{
			memcpy(data, &buf->buf[buf->tail], partial_size);
			size -= partial_size;
			data += partial_size;
			memcpy(data, buf->buf, size);
			buf->tail = size;
		}
		else
		{
			memcpy(data, &buf->buf[buf->tail], size);
			buf->tail += size;
		}
		if (buf->head == buf->tail) buf->status = HAE_LINER_BUF_EMPTY; else buf->status = HAE_LINER_BUF_FILLED;
	}
	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&buf->lock);
	return data_size;
}

static void haeLocalLinerBuf_end(HaeLocalLinerBuf *buf)
{
	pthread_mutex_lock(&buf->lock);
	pthread_cleanup_push(mutex_unlock, (void *)&buf->lock);

	buf->flag = HAE_LINER_BUF_INPUT_END;
	pthread_cond_signal(&buf->cond);

	pthread_cleanup_pop(1); // (mutex_unlock, (void *)&buf->lock);
}

static int haeLocalLinerBuf_getchar(HaeLocalLinerBuf *buf)
{
	char c[1];
	if (buf->pop(buf, (u8_t *)c, 1) == 0) return EOF;
	else return c[0] & 0x000000ff;
}

HaeLocalLinerBuf *_haeLocalLinerBuf_create(int size, int *err HAE_LOCAL_MEMORY_TRC_ARG)
{
	int local_err;
	int *err_p = err ? err : &local_err;
	HaeLocalLinerBuf *ret = NULL;
	if (size == 0) { *err_p = EINVAL; return NULL; }

	*err_p = 0;

	if (!(ret = (HaeLocalLinerBuf *)LOCAL_MALLOC_TRC(sizeof(HaeLocalLinerBuf))))
	{
		HaeOut->fprintf(stdout, 0, "haeLocalLinerBuf_create() : Memory allocation error\n");
		exit(1);
	}
	ret->size = size;
	ret->head = 0;
	ret->tail = 0;
	ret->status = HAE_LINER_BUF_EMPTY;
	ret->flag = HAE_LINER_BUF_INPUT_NORMAL;
	if (!(ret->buf = (u8_t *)malloc(sizeof(u8_t) * size)))
	{ 
		HaeOut->fprintf(stdout, 0, "haeLocalLinerBuf_create() : Memory allocation error\n");
		exit(1);
	}
	pthread_mutex_init(&ret->lock, NULL);
	pthread_cond_init(&ret->cond, NULL);
	ret->push = haeLocalLinerBuf_push;
	ret->pop = haeLocalLinerBuf_pop;
	ret->popWait = haeLocalLinerBuf_popWait;
	ret->end = haeLocalLinerBuf_end;
	ret->getchar = haeLocalLinerBuf_getchar;
	return ret;
}

void haeLocalLinerBuf_del(HaeLocalLinerBuf *buf)
{
	HaeOut->fprintf(stdout, 0, "haeLocalLinerBuf_del() : Called\n");
	if (!buf) return;
	if (buf->buf) free(buf->buf);
	pthread_mutex_destroy(&buf->lock);
	pthread_cond_destroy(&buf->cond);
	LOCAL_FREE(buf);
}

void haeLocalLinerBuf_dump(HaeLocalLinerBuf *p, int tab)
{
	if (!p) return;
	HaeOut->printf(tab, "[Size:%d][Status:%s][Flag:%s]\n", p->size,
			p->status == HAE_LINER_BUF_FILLED ? "Filled" : p->status == HAE_LINER_BUF_FULL ? "Full" : "Empty",
			p->flag == HAE_LINER_BUF_INPUT_END ? "Closed" : "Opened");
}

void haeLocalLinerBuf_cancel(void *p) { haeLocalLinerBuf_del((HaeLocalLinerBuf *)p); }

#include <dz1_malloc.h>
#include "dz1_thread_hash.h"

///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Bucket
///////////////////////////////////////////////////////////////////////////////
static Dz1ThreadBucket *Dz1ThreadBucket_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	//Dz1ThreadBucket *ret = (Dz1ThreadBucket *)malloc(sizeof(Dz1ThreadBucket));
	Dz1ThreadBucket *ret = (Dz1ThreadBucket *)Dz1Malloc(sizeof(Dz1ThreadBucket), errp);
	if (ret == NULL) Dz1Error_set(errp, ENOMEM);
	else
	{
		ret->prev = ret;
		ret->next = ret;
		ret->slot = NULL;
		Dz1Error_set(errp, 0);
	}
	return ret;
}

static void Dz1ThreadBucket_del(Dz1ThreadBucket *p)
{
	if (!p) return;
	if (p->slot) Dz1ThreadEntry_del(p->slot);
	Dz1Free(p);
}

static int Dz1ThreadBucket_count(Dz1ThreadBucket *p)
{
	int cnt = 0;
	Dz1ThreadBucket *i;
	if (p)
	{
		for (i = p; i->next != p; i = i->next) cnt++;
		cnt++;
	}
	return cnt;
}
///////////////////////////////////////////////////////////////////////////////
// DZ1 Thread Hash
///////////////////////////////////////////////////////////////////////////////
Dz1ThreadEntry *Dz1ThreadHash_add(Dz1ThreadHash *p, u32_t id, Dz1ThreadLogLevel level, 
								  Dz1Console *con, str_t name, Dz1ThreadFunc func, Dz1Error *fret, Dz1Error *err)
{
	Dz1ThreadEntry *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1ThreadBucket *b = Dz1ThreadBucket_new(errp);
	if (b != NULL)
	{
		pthread_cleanup_push((Dz1CancelFunc)Dz1ThreadBucket_del, (void *)&b);

		if ((ret = b->slot = Dz1ThreadEntry_new(b, id, pthread_self(), level, con, name, func, fret, errp)) != NULL)
		{
#ifdef PTW32_VERSION
			u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)(b->slot->th.p) % DZ1_THREAD_HASH_SIZE);
#else
			u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)(b->slot->th) % DZ1_THREAD_HASH_SIZE);
#endif
			if (p->bucket[idx])
			{
				p->bucket[idx]->next->prev = b;
				b->next = p->bucket[idx]->next;
				p->bucket[idx]->next = b;
				b->prev = p->bucket[idx];
			}
			else p->bucket[idx] = b;
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // ((Dz1CancelFunc)Dz1ThreadBucket_del, (void *)&b);
	}
	return ret;
}

void Dz1ThreadHash_remove(Dz1ThreadHash *p, Dz1ThreadEntry *e)
{
#ifdef PTW32_VERSION
	u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)e->th.p % DZ1_THREAD_HASH_SIZE);
#else
	u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)e->th % DZ1_THREAD_HASH_SIZE);
#endif
	Dz1ThreadBucket *dst = e->bucket;

	if (dst == p->bucket[idx])
	{	// Head
		if (dst->prev == dst->next)
			p->bucket[idx] = NULL;	// Just One Entry
		else
			p->bucket[idx] = dst->next;
	}

	dst->next->prev = dst->prev;
	dst->prev->next = dst->next;

	Dz1ThreadBucket_del(dst);
}

Dz1ThreadEntry *Dz1ThreadHash_find(Dz1ThreadHash *p, Dz1ThreadEntry *key)
{
	Dz1ThreadEntry *ret = NULL;
#ifdef PTW32_VERSION
	u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)key->th.p % DZ1_THREAD_HASH_SIZE);
#else
	u32_t idx = (u32_t)((DZ1_PTR_SIZED_TYPE)key->th % DZ1_THREAD_HASH_SIZE);
#endif
	if (p->bucket[idx])
	{
		Dz1ThreadBucket *b = p->bucket[idx];
		do
		{
			if (pthread_equal(b->slot->th, key->th)) { ret = p->bucket[idx]->slot; break; }
			else b = b->next;
		} while(b != p->bucket[idx]);
	}
	return ret;
}

double Dz1ThreadHash_analysis(Dz1ThreadHash *p)
{
	int i;
	int cnt = 0, th = 0;
	double ret = 0.0;
	for (i = 0; i < DZ1_THREAD_HASH_SIZE; i++)
	{
		if (p->bucket[i])
		{
			cnt++;
			th += Dz1ThreadBucket_count(p->bucket[i]);
		}
	}
	if (cnt) ret = (double)th / (double)cnt;
	return ret;
}

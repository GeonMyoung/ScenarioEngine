#include <pthread.h>
#include <hae_errors.h>

#include "hae_output.h"
#include "hae_local_memory.h"
#include "hae_local_hash.h"

struct HaeLocalHashSlotListCtl
{
	HaeLocalHashSlotList *(*create)(void *);
	void (*del)(struct HaeLocalHashSlotList *, void (*dataDel)(void *));
	void (*dump)(struct HaeLocalHashSlotList *, void (*dataDump)(void *, int), int);
	void (*info)(struct HaeLocalHashSlotList *, void (*dataInfo)(void *, int), int);
	void (*link)(struct HaeLocalHashSlotList **, struct HaeLocalHashSlotList *);
	void (*unlink)(struct HaeLocalHashSlotList **, struct HaeLocalHashSlotList *);
	HaeLocalHashSlotList *(*find)(struct HaeLocalHashSlotList *, int (*cmp)(void *, void *), void *);
	int (*getSize)(struct HaeLocalHashSlotList *);
};

extern struct HaeLocalHashSlotListCtl HaeLocalHashSlotListCtl;

struct HaeLocalHashBucketCtl
{
	HaeLocalHashBucket *(*create)(HaeLocalHashSlotList *);
	void (*del)(HaeLocalHashBucket *, void (*dataDel)(void *));
};

extern struct HaeLocalHashBucketCtl HaeLocalHashBucketCtl;

u16_t haeLocalHashKey_foldSum16(void *source, int len, u16_t actualSize)
{
	u16_t *temp = NULL, key = 0;
	int size, seg, inc, i;
	if (!source)
	{
		return 0;
	}
	seg = len / sizeof(u16_t);
	inc = len % sizeof(u16_t);
	size = seg + inc ? 1 : 0;
	temp = (u16_t *)malloc(sizeof(u16_t) * size);
	if (!temp)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHashKey_foldSum16() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	else
	{
		memset(temp, 0, sizeof(u16_t) * size);
		memcpy(temp, source, len);
	}
	for (i = 0; i < size; i++)
		key += temp[i];
	free(temp);
	return key % actualSize;
}

u32_t haeLocalHashKey_foldSum32(void *source, int len, u32_t actualSize)
{
	u32_t *temp = NULL, key = 0;
	int size, seg, inc, i;
	if (!source)
	{
		return 0;
	}
	seg = len / sizeof(u32_t);
	inc = len % sizeof(u32_t);
	size = seg + (inc ? 1 : 0);
	temp = (u32_t *)malloc(sizeof(u32_t) * size);
	if (!temp)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHashKey_foldSum32() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	else
	{
		memset(temp, 0, sizeof(u32_t) * size);
		memcpy(temp, source, len);
	}
	for (i = 0; i < size; i++)
		key += temp[i];
	free(temp);
	return key % actualSize;
}

HaeLocalHashDataParam *_haeLocalHashDataParam_create(u32_t (*hashKey)(void *, u32_t), void (*dataDel)(void *),
											  void (*dataDump)(void *, int), void (*dataInfo)(void *, int), 
											  int (*dataCmp)(void *, void *) HAE_LOCAL_MEMORY_TRC_ARG)
{
	int old_cancel_state;
	HaeLocalHashDataParam *ret = NULL;

	if (!hashKey || !dataDel || !dataDump || !dataCmp) return NULL;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	ret = (HaeLocalHashDataParam *)LOCAL_MALLOC_TRC(sizeof(HaeLocalHashDataParam));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHashDataParam_create() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	ret->hashKey = hashKey;
	ret->dataDel = dataDel;
	ret->dataDump = dataDump;
	ret->dataInfo = dataInfo;
	ret->dataCmp = dataCmp;
	pthread_setcancelstate(old_cancel_state, NULL);
	return ret;
}

void haeLocalHashDataParam_del(HaeLocalHashDataParam *p)
{
	int old_cancel_state;
	if (!p) return;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	LOCAL_FREE(p);
	pthread_setcancelstate(old_cancel_state, NULL);
}

static HaeLocalHashSlotList *haeLocalHashSlotList_new(void *data)
{
	int old_cancel_state;
	HaeLocalHashSlotList *ret = NULL;

	if (!data) return NULL;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	ret = (HaeLocalHashSlotList *)malloc(sizeof(HaeLocalHashSlotList));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHashSlotList_new() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	ret->data = data;
	ret->next = NULL;
	pthread_setcancelstate(old_cancel_state, NULL);
	return ret;
}

static void haeLocalHashSlotList_del(HaeLocalHashSlotList *list, void (*dataDel)(void *))
{
	int old_cancel_state;
	HaeLocalHashSlotList *p = list, *next = NULL;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	while(p)
	{
		next = p->next;
		if (p->data && dataDel) dataDel(p->data);
		free(p);
		p = next;
	}
	pthread_setcancelstate(old_cancel_state, NULL);
}

static void haeLocalHashSlotList_dump(HaeLocalHashSlotList *list, void (*dataDump)(void *, int), int tab)
{
	if (!list)
		HaeOut->printf(tab, "[Slot Empty]\n");
	else
	{
		for (; list; list = list->next)
			if (list->data) dataDump(list->data, tab);
	}
}

static void haeLocalHashSlotList_info(HaeLocalHashSlotList *list, void (*dataInfo)(void *, int), int tab)
{
	if (!dataInfo) return;
	if (!list)
		HaeOut->printf(tab, "[Slot Empty]\n");
	else
	{
		for (; list; list = list->next)
			if (list->data) dataInfo(list->data, tab);
	}
}

static void haeLocalHashSlotList_link(HaeLocalHashSlotList **list, HaeLocalHashSlotList *node)
{
	if (*list) node->next = *list;
	*list = node;
}

static void haeLocalHashSlotList_unlink(HaeLocalHashSlotList **list, HaeLocalHashSlotList *node)
{
	HaeLocalHashSlotList *p = *list, **pprev = list;
	while(p)
	{
		if (p == node)
		{
			*pprev = p->next;
			p->next = NULL;
			break;
		}
		pprev = &p->next;
		p = p->next;
	}
}

static HaeLocalHashSlotList *haeLocalHashSlotList_find(HaeLocalHashSlotList *list, int (*cmp)(void *, void *), void *key)
{
	if (!key) return NULL;
	for (; list; list = list->next)
		if (list->data && cmp(list->data, key) == 0) return list;
	return NULL;
}

static int haeLocalHashSlotList_getSize(HaeLocalHashSlotList *list)
{
	int ret = 0;
	for (; list; list = list->next) ret++;
	return ret;
}

struct HaeLocalHashSlotListCtl HaeLocalHashSlotListCtl =
{
	haeLocalHashSlotList_new,
	haeLocalHashSlotList_del,
	haeLocalHashSlotList_dump,
	haeLocalHashSlotList_info,
	haeLocalHashSlotList_link,
	haeLocalHashSlotList_unlink,
	haeLocalHashSlotList_find,
	haeLocalHashSlotList_getSize
};

static int haeLocalHashBucket_add(HaeLocalHashBucket *bucket, void *data)
{
	HaeLocalHashSlotList *node = NULL;
	if (!data) return FALSE;
	node = HaeLocalHashSlotListCtl.create(data);
	HaeLocalHashSlotListCtl.link(&bucket->slot, node);
	return TRUE;
}

static int haeLocalHashBucket_remove(HaeLocalHashBucket *bucket, 
								int (*dataCmp)(void *, void *), void (*dataDel)(void *), void *key)
{
	HaeLocalHashSlotList *node = NULL;
	if (!key) return FALSE;
	node = HaeLocalHashSlotListCtl.find(bucket->slot, dataCmp, key);
	if (node)
	{
		HaeLocalHashSlotListCtl.unlink(&bucket->slot, node);
		HaeLocalHashSlotListCtl.del(node, dataDel);
	}
	return TRUE;
}

static void haeLocalHashBucket_dump(HaeLocalHashBucket *bucket, void (*dataDump)(void *, int), int tab)
{
	if (bucket->slot) HaeLocalHashSlotListCtl.dump(bucket->slot, dataDump, tab);
}

static void haeLocalHashBucket_info(HaeLocalHashBucket *bucket, void (*dataInfo)(void *, int), int tab)
{
	if (!dataInfo) return;
	if (bucket->slot) HaeLocalHashSlotListCtl.info(bucket->slot, dataInfo, tab);
}

static void *haeLocalHashBucket_find(HaeLocalHashBucket *bucket, int (*dataCmp)(void *, void *), void *key)
{
	HaeLocalHashSlotList *node = NULL;
	node = HaeLocalHashSlotListCtl.find(bucket->slot, dataCmp, key);
	if (node) return node->data;
	else return NULL;
}

static HaeLocalHashSlotList *haeLocalHashBucket_extract(HaeLocalHashBucket *bucket, int (*dataCmp)(void *, void *), void *key)
{
	HaeLocalHashSlotList *node = NULL;
	node = HaeLocalHashSlotListCtl.find(bucket->slot, dataCmp, key);
	if (node)
	{
		HaeLocalHashSlotListCtl.unlink(&bucket->slot, node);
		return node;
	}
	else return NULL;
}

static HaeLocalHashBucket *haeLocalHashBucket_new(HaeLocalHashSlotList *list)
{
	int old_cancel_state;
	HaeLocalHashBucket *ret = NULL;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	ret = (HaeLocalHashBucket *)malloc(sizeof(HaeLocalHashBucket));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHashBucket_new() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	pthread_setcancelstate(old_cancel_state, NULL);
	ret->slot = list;
	ret->add = haeLocalHashBucket_add;
	ret->remove = haeLocalHashBucket_remove;
	ret->dump = haeLocalHashBucket_dump;
	ret->info = haeLocalHashBucket_info;
	ret->find = haeLocalHashBucket_find;
	ret->extract = haeLocalHashBucket_extract;
	return ret;
}

static void haeLocalHashBucket_del(HaeLocalHashBucket *p, void (*dataDel)(void *))
{
	int old_cancel_state;
	if (!p) return;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	if (p->slot) HaeLocalHashSlotListCtl.del(p->slot, dataDel);
	free(p);
	pthread_setcancelstate(old_cancel_state, NULL);
}

struct HaeLocalHashBucketCtl HaeLocalHashBucketCtl =
{
	haeLocalHashBucket_new,
	haeLocalHashBucket_del
};

static int haeLocalHash_add(HaeLocalHash *hash, void *data)
{
	u32_t idx;
	if (!data) return FALSE;
	idx = hash->param->hashKey(data, hash->actualSize);
	return hash->bucket[idx]->add(hash->bucket[idx], data);
}

static int haeLocalHash_remove(HaeLocalHash *hash, void *key)
{
	u32_t idx;
	if (!key) return FALSE;
	idx = hash->param->hashKey(key, hash->actualSize);
	return hash->bucket[idx]->remove(hash->bucket[idx], hash->param->dataCmp, hash->param->dataDel, key);
}

static void haeLocalHash_dump(HaeLocalHash *hash, int tab)
{
	u32_t i;
	for (i = 0; i < hash->actualSize; i++)
		hash->bucket[i]->dump(hash->bucket[i], hash->param->dataDump, tab);
}

static void haeLocalHash_info(HaeLocalHash *hash, int tab)
{
	u32_t i;
	for (i = 0; i < hash->actualSize; i++)
		hash->bucket[i]->info(hash->bucket[i], hash->param->dataInfo, tab);
}

static void *haeLocalHash_find(HaeLocalHash *hash, void *key)
{
	u32_t idx;
	if (!key) return NULL;
	idx = hash->param->hashKey(key, hash->actualSize);
	return hash->bucket[idx]->find(hash->bucket[idx], hash->param->dataCmp, key);
}

static void *haeLocalHash_extract(HaeLocalHash *hash, void *key)
{
	u32_t idx;
	HaeLocalHashSlotList *node = NULL;
	if (!key) return NULL;
	idx = hash->param->hashKey(key, hash->actualSize);
	if ((node = hash->bucket[idx]->extract(hash->bucket[idx], hash->param->dataCmp, key)))
	{
		void *data = node->data;
		node->data = NULL;
		HaeLocalHashSlotListCtl.del(node, hash->param->dataDel);
		return data;
	}
	else
		return NULL;
}

static int haeLocalHash_isEmpty(HaeLocalHash *hash)
{
	u32_t i;
	for (i = 0; i < hash->actualSize; i++)
		if (hash->bucket[i]) return FALSE;
	return TRUE;
}

static u32_t leastPrime(u32_t value)
{
	u32_t ret = value, i;
	int isPrime = TRUE;

	if (ret <= 3) return 3;

	while(1)
	{
		for (i = 2; i <= ret / 2; i++)
		{
			isPrime = TRUE;
			if (ret % i == 0)
			{
				isPrime = FALSE;
				break;
			}
		}
		if (isPrime) break;
		ret++;
	}
	return i;
}

HaeLocalHash *_haeLocalHash_create(u32_t size, HaeLocalHashDataParam *param HAE_LOCAL_MEMORY_TRC_ARG)
{
	u32_t i;
	int old_cancel_state;
	HaeLocalHash *ret = NULL;
	if (!size || !param) return NULL;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	ret = (HaeLocalHash *)LOCAL_MALLOC_TRC(sizeof(HaeLocalHash));
	if (!ret)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHash_create() : %s\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	ret->size = size;
	ret->actualSize = leastPrime(size);
	ret->bucket = (HaeLocalHashBucket **)malloc(sizeof(HaeLocalHashBucket **) * ret->actualSize);
	if (!ret->bucket)
	{
		HaeOut->fprintf(stdout, 0, "haeLocalHash_create() : %s for bucket\n", HAE_ERR_STR_LOCAL_MALLOC);
		exit(1);
	}
	for (i = 0; i < ret->actualSize; i++)
	{
		ret->bucket[i] = HaeLocalHashBucketCtl.create(NULL);
		if (!ret->bucket[i])
		{
			HaeOut->fprintf(stdout, 0, "haeLocalHash_create() : Bucket[%d] Create Fail\n", i);
			exit(1);
		}
	}
	pthread_setcancelstate(old_cancel_state, NULL);
	ret->param = param;
	ret->add = haeLocalHash_add;
	ret->remove = haeLocalHash_remove;
	ret->dump = haeLocalHash_dump;
	ret->info = haeLocalHash_info;
	ret->find = haeLocalHash_find;
	ret->extract = haeLocalHash_extract;
	ret->isEmpty = haeLocalHash_isEmpty;
	return ret;
}

void haeLocalHash_del(HaeLocalHash *hash)
{
	int old_cancel_state;
	if (!hash) return;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
	if (hash->bucket)
	{
		u32_t i;
		for (i = 0 ;i<hash->actualSize; i++)
			HaeLocalHashBucketCtl.del(hash->bucket[i], hash->param->dataDel);
		free(hash->bucket);
	}
	if (hash->param) haeLocalHashDataParam_del(hash->param);
	LOCAL_FREE(hash);
	pthread_setcancelstate(old_cancel_state, NULL);
}

HaeLocalHashCursor haeLocalHashCursor_init(HaeLocalHash *hash)
{
	HaeLocalHashCursor ret = { NULL, -1, hash };
	u32_t i;
	for (i = 0; i < hash->actualSize; i++)
	{
		if (hash->bucket[i] && hash->bucket[i]->slot)
		{
			ret.p = hash->bucket[i]->slot;
			ret.bucketIdx = i;
			break;
		}
	}
	return ret;
}

int haeLocalHashCursor_cond(HaeLocalHashCursor *c)
{
	if (!c)
		return FALSE;
	if (!c->p)
		return FALSE;
	return TRUE;
}

HaeLocalHashCursor haeLocalHashCursor_next(HaeLocalHashCursor c)
{
	if (c.p)
	{
		if (c.p->next)
			c.p = c.p->next;
		else
		{
			u32_t i;
			c.p = NULL;
			for (i = c.bucketIdx+1; i < c.hash->actualSize; i++)
			{
				if (c.hash->bucket[i] && c.hash->bucket[i]->slot)
				{
					c.p = c.hash->bucket[i]->slot;
					c.bucketIdx = i;
					break;
				}
			}
		}
	}
	return c;
}

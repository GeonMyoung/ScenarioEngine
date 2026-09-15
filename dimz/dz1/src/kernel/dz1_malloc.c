#include <dz1.h>

#ifndef MAC_OS_X
#include <malloc.h>
#endif

#include <dz1_stdio.h>
#include <dz1_malloc.h>

#include <dz1_thread_stdio.h>

#define DZ1_MEMORY_MAGIC_ALLOC			0xFF0FF0FF
#define DZ1_MEMORY_MAGIC_FREE			0x66F66F66

typedef struct Dz1MemFrag
{
	unsigned int magic;
	char filename[DZ1_PATH_FILE_STR_SIZE];
	int lineNum;
	int size;
	int freezNum;
	struct Dz1MemFrag *prev;
	struct Dz1MemFrag *next;
} Dz1MemFrag;


typedef struct Dz1Mem
{
	__DZ1ALIGN(u32_t, malloc_cnt);
	__DZ1ALIGN(u32_t, free_cnt);
	__DZ1ALIGN(int, currentFreez);
	Dz1MemFrag *history;
	__DZ1ALIGN(pthread_mutex_t, lock);
} Dz1Mem;

static Dz1Mem _Dz1Mem_ =
{
	0, { 0, },
	0, { 0, },
	0, { 0, },
	NULL,
	PTHREAD_MUTEX_INITIALIZER
};

static Dz1Mem *dz1Mem = &_Dz1Mem_;

#define GetUserPtr(x)			((u8_t *)(x) + sizeof(Dz1MemFrag))
#define GetCorePtr(x)			((u8_t *)(x) - sizeof(Dz1MemFrag))

static Dz1MemFrag *Dz1MemFrag_new(size_t size, Dz1Error *err, const char *filename, int lineNum)
{
	Dz1MemFrag *ret = (Dz1MemFrag *)malloc(size + sizeof(Dz1MemFrag));
	if (ret == NULL) Dz1Error_set(err, ENOMEM);
	else
	{

		ret->magic = DZ1_MEMORY_MAGIC_ALLOC;

		if (filename)
		{
			char *fn = (char *)filename;
			int len = (int)strlen(filename);
			if (len >= (int)DZ1_PATH_FILE_STR_SIZE)			// len = 5, SIZE = 5
			{
				len -= (DZ1_PATH_FILE_STR_SIZE - 1);		// len = 5 - 4 = 1
				fn += len;									// fn = fn + 1;
				len = DZ1_PATH_FILE_STR_SIZE - 1;			// len = 4
			}
			memcpy(ret->filename, fn, len);					// 4byte copy(0~3)
			ret->filename[len] = 0;							// 

			// if (len > 48) { len = len >> 1; fn += len; }
			// strncpy(ret->filename,  fn, 63);
			// ret->filename[DZ1_PATH_FILE_STR_SIZE - 1] = '\0';
		}
		else
			strcpy(ret->filename, "(system)");

		ret->lineNum = lineNum;

		ret->size = (int)size;

		ret->freezNum = dz1Mem->currentFreez;

		ret->prev = ret;
		ret->next = ret;

	}
	return ret;
}

void *_Dz1Malloc(size_t size, Dz1Error *err, const char *filename, int lineNum)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1MemFrag *i = Dz1MemFrag_new(size, errp, filename, lineNum);
	if (i != NULL)
	{
		pthread_mutex_lock(&dz1Mem->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

		if (dz1Mem->history)
		{
			i->prev = dz1Mem->history;
			i->next = dz1Mem->history->next;
			dz1Mem->history->next->prev = i;
			dz1Mem->history->next = i;
		}
		else dz1Mem->history = i;

		dz1Mem->malloc_cnt++;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);
	}

	return (void *)GetUserPtr(i);
}

void *_Dz1Calloc(size_t unit, size_t numb, Dz1Error *err, const char *filename, int lineNum)
{
	size_t size = unit * numb;
	void *ret = _Dz1Malloc(size, err, filename, lineNum);
	if (ret) memset(ret, 0, size);
	return ret;
}

static void *traking_ptr = NULL;

void _Dz1Free(void *ptr, const char *file, int line)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (!ptr) 
	{ 
		Dz1Error_set(errp, EINVAL); 
		printf("!!! try to free NULL from %s:%d\n", file, line); 
	}
	else
	{
		Dz1MemFrag *i = (Dz1MemFrag *)GetCorePtr(ptr);

		if (traking_ptr != NULL && traking_ptr == ptr)
			ptr = ptr;
 		if (i->magic != DZ1_MEMORY_MAGIC_ALLOC)
		{
			int temp = 0;
			if (i->magic == DZ1_MEMORY_MAGIC_FREE)
			{
				Dz1Error_setWithComment(errp, ESRCH, (DZ1_ERROR_ARG, "Free Twice %s:%d, %s:%d", file, line, i->filename, i->lineNum));
				printf("Free Twice %s:%d is freed\n", i->filename, i->lineNum);
			}
			else
			{
				Dz1Error_setWithComment(errp, EINVAL, (DZ1_ERROR_ARG, "Invalid Free at %s:%d", file, line));
				printf("invalid free (MAGIC:%08X %s:%d), %s:%d\n", i->magic, i->filename, i->lineNum, file, line);
			}
			memcpy(&temp, (void *)0x10, sizeof(int)); // Generate SEGV
		}

		pthread_mutex_lock(&dz1Mem->lock);
		pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

		if (i == dz1Mem->history) dz1Mem->history = dz1Mem->history->next;

		if (i->prev == i && i->next == i) dz1Mem->history = NULL;
		else
		{
			i->prev->next = i->next;
			i->next->prev = i->prev;
			i->prev = i->next = i;
		}

		dz1Mem->free_cnt++;

		pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

		i->magic = DZ1_MEMORY_MAGIC_FREE;
		i->filename[0] = 0;
		i->lineNum = 0;


		
		free(i);
	}
}

void Dz1Mem_setTracker(void *ptr)
{
	traking_ptr = ptr;
}

int Dz1Mem_getFreez(void)
{
	int oldFreezNum;

	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	oldFreezNum = dz1Mem->currentFreez;

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	return oldFreezNum;
}

int Dz1Mem_freez(void)
{
	int oldFreezNum;

	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	oldFreezNum = dz1Mem->currentFreez = dz1Mem->currentFreez < 0x7fffffff ? dz1Mem->currentFreez + 1 : 0x7fffffff;

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	return oldFreezNum;
}

int Dz1Mem_melt(void)
{
	int oldFreezNum;

	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	oldFreezNum = dz1Mem->currentFreez > 0 ? dz1Mem->currentFreez - 1 : 0;

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	return oldFreezNum;
}

void Dz1MemA_export(FILE *fp, int binDump)
{
	if (!fp) return;
	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	if (dz1Mem->history)
	{
		Dz1MemFrag *i = dz1Mem->history;
		do
		{
			fprintf(fp, "[ADDR:0x%p][SIZE:0x%08x][%s:%d]\n", GetUserPtr(i), i->size, i->filename, i->lineNum);
			if (binDump) Dz1A_ftprintb(fp, 1, GetUserPtr(i), i->size, 16);
			i = i->prev;
		} while(i != dz1Mem->history);
		fprintf(fp, "MALLOC:%u FREE:%u REMAIN:%u\n", dz1Mem->malloc_cnt, dz1Mem->free_cnt, dz1Mem->malloc_cnt - dz1Mem->free_cnt);
	}
	else fprintf(fp, "No Memory Leak\n");

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);
}

#ifndef UNIX_SYSTEM
static void _quick_8bit_unicode_conv(wchar_t *dst, char *src)
{
	size_t sz = DZ1_PATH_FILE_STR_SIZE;
	char *cp = src;
	wchar_t *dp = dst;
	while(*cp && sz > 1)
	{
//		if (*cp <= 255) *dp = (wchar_t)*cp;
//		else *dp = L'?';
		*dp = (wchar_t)*cp & 0xFF;
		dp++;
		cp++;
		sz--;
	}
	*dp = 0;
}

void Dz1MemW_export(FILE *fp, int binDump)
{
	if (!fp) return;
	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	if (dz1Mem->history)
	{
		wchar_t filename[DZ1_PATH_FILE_STR_SIZE];
		Dz1MemFrag *i = dz1Mem->history;
		do
		{
			_quick_8bit_unicode_conv(filename, i->filename);
			Dz1W_fprintf(fp, L"[ADDR:0x%p][SIZE:0x%08x][%s:%d]\n", GetUserPtr(i), i->size, filename, i->lineNum);
			if (binDump) Dz1W_ftprintb(fp, 1, GetUserPtr(i), i->size, 16);
			i = i->prev;
		} while(i != dz1Mem->history);
		Dz1W_fprintf(fp, L"MALLOC:%u FREE:%u REMAIN:%u\n", dz1Mem->malloc_cnt, dz1Mem->free_cnt, dz1Mem->malloc_cnt - dz1Mem->free_cnt);
	}
	else Dz1W_fprintf(fp, L"No Memory Leak\n");

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);
}
#endif

void Dz1MemA_dump(int freezNum, int dump_bin, int tab)
{
	u32_t freezedCnt = 0;

	if (freezNum < 0) freezNum = dz1Mem->currentFreez;

	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	if (dz1Mem->history)
	{
		Dz1MemFrag *i = dz1Mem->history;
		do
		{
			if (i->freezNum >= freezNum)
			{
				Dz1ThreadA_tprintf(tab, "[ADDR:0x%p][SIZE:0x%08x][FREEZNUM:%d][%s:%d]\n", GetUserPtr(i), i->size, i->freezNum, i->filename, i->lineNum);
				if (dump_bin) Dz1ThreadA_tprintb(tab + 1, GetUserPtr(i), i->size, 16, TRUE);
				freezedCnt++;
			}
			i = i->prev;
		} while(i != dz1Mem->history);
		Dz1ThreadA_tprintf(tab, "MALLOC:%u FREE:%u REMAIN:%u FREEZ(%d):%u\n",
										dz1Mem->malloc_cnt, dz1Mem->free_cnt,
										dz1Mem->malloc_cnt - dz1Mem->free_cnt,
										freezNum, freezedCnt);
	}
	else Dz1ThreadA_tprintf(tab, "No Memory Leak\n");

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);
}

#ifndef UNIX_SYSTEM
void Dz1MemW_dump(int freezNum, int dump_bin, int tab)
{
	u32_t freezedCnt = 0;

	if (freezNum < 0) freezNum = dz1Mem->currentFreez;

	pthread_mutex_lock(&dz1Mem->lock);
	pthread_cleanup_push((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);

	if (dz1Mem->history)
	{
		wchar_t filename[DZ1_PATH_FILE_STR_SIZE];
		Dz1MemFrag *i = dz1Mem->history;
		do
		{
			if (i->freezNum >= freezNum)
			{
				_quick_8bit_unicode_conv(filename, i->filename);
				Dz1ThreadW_tprintf(tab, L"[ADDR:0x%p][SIZE:0x%08x][FREEZNUM:%d][%s:%d]\n", GetUserPtr(i), i->size, i->freezNum, filename, i->lineNum);
				if (dump_bin) Dz1ThreadW_tprintb(tab + 1, GetUserPtr(i), i->size, 16, TRUE);
				freezedCnt++;
			}
			i = i->prev;
		} while(i != dz1Mem->history);
		Dz1ThreadW_tprintf(tab, L"MALLOC:%u FREE:%u REMAIN:%u FREEZ(%d):%u\n",
										dz1Mem->malloc_cnt, dz1Mem->free_cnt,
										dz1Mem->malloc_cnt - dz1Mem->free_cnt,
										freezNum, freezedCnt);
	}
	else Dz1ThreadW_tprintf(tab, L"No Memory Leak\n");

	pthread_cleanup_pop(1); // ((Dz1CancelFunc)pthread_mutex_unlock, (void *)&dz1Mem->lock);
}
#endif
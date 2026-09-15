#include <dz1_cleanup.h>

#include <dz1_stdio.h>
#include <dz1_riff_util.h>

#ifdef _DEBUG
#include <conio.h>
#endif

static FILE *logfp = NULL;
static void _outputHook(void *ptr, unsigned char *data, size_t size)
{
	if (logfp != NULL)
	{
		fwrite(data, size, 1, logfp);
		fflush(logfp);
	}
}
static void _memoryExport(void *ptr) { if (logfp) Dz1Mem_export(logfp, TRUE); }

static bool_t my_memcmp(u8_t *a, u8_t *b, size_t size)
{
	size_t i;
	bool_t ret = TRUE;
	for (i = 0; i < size; i++)
	{
		if (a[i] != b[i])
		{
			ret = FALSE;
			Dz1Thread_printf("my_memcmp() : POS=%d, A=0x%02X, B=0x%02X\n", i + 1, a[i], b[i]);
		}
	}
	return ret;
}

static bool_t _riff_save(Dz1Str path, Dz1Str name, Dz1Riff *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = Dz1FileStream_open3(path, name, "wav", "wb", errp);
	if (fp == NULL) ERR_OUT(errp);
	else
	{
		ssize_t status;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((status = Dz1Riff_save(fp, src, errp)) < 0) ERR_OUT(errp);
		else
		{
			Dz1Thread_printf("Save Byte = %d\n", status);
			Dz1Error_set(errp, 0);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ERR_IS_SUCCESS(errp);
}

int main(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1Cleanup_init();

	Dz1Str path = Dz1T("..\\..");
	Dz1Str src_name = Dz1T("sample");
	Dz1Str dst_name = Dz1T("output");
	Dz1Str ext = Dz1T("wav");

	Dz1Riff *riff = NULL;
	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_syslogTest.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif

	if ((riff = Dz1Riff_new(NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		ssize_t size = 0, status;
		u8_t *dst = NULL;
		Dz1Binary *src = NULL;
		
		pthread_cleanup_push((Dz1DelFunc)Dz1Riff_del, riff);
		if ((src = Dz1BinFile_load3(path, src_name, ext, &err)) == NULL)
		{
			Dz1Thread_printf(Dz1T("%s, %s.%s\n"), path, src_name, ext);
			ERR_OUT(&err);
		}
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1Binary_del, (void *)src);

			Dz1Thread_printf("File Loaded %d bytes\n", src->size);

			if ((status = Dz1Riff_dec(riff, src->data, src->size, &err)) < 0) ERR_OUT(&err);
			else
			{
				Dz1Thread_printf("Riff = "); Dz1Riff_dump(riff, 0);

				if ((size = Dz1Riff_enc(NULL, -1, riff, &err)) < 0) ERR_OUT(&err);
				else if ((dst = (u8_t *)Dz1Malloc(size, &err)) == NULL) ERR_OUT(&err);
				else
				{
					pthread_cleanup_push(Dz1Memory_cancel, (void *)dst);

					if ((size = Dz1Riff_enc(dst, size, riff, &err)) < 0) ERR_OUT(&err);
					else if (src->size != size) ERR_SET_OUT(&err, EFAULT);
					else if (my_memcmp(src->data, dst, src->size) == FALSE) ERR_SET_OUT(&err, EINVAL);
					else
					{
						Dz1Thread_printf("Encoded size = %u\n", size);
						_riff_save(path, dst_name, riff, NULL);
					}
					pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)dst);
				}
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Binary_del, (void *)bin);
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Riff_del, riff);
	}
#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#endif

#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
	return err.code;
}
//#include <dz1_lzw.h>

#include <dz1_cleanup.h>
#include <dz1_shell.h>
#include <dz1_socket.h>
#include <dz1_bmp.h>

#include <Dz1GifCodec.h>
#include <Dz1GifUtil.h>

// #include "lzw.h"

#ifdef _DEBUG
#include <conio.h>
#endif
/*
static Dz1Error _lzw_test(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	u8_t min_code_size = 4;

	lzw_t *lzw = NULL;
	LzwStream fin, fout;
	u8_t native_buf[] = { 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x01, 0x02 };
	u8_t comp_buf[1024], decomp_buf[1024];
	size_t comp_size = 0, decomp_size = 0, native_buf_size = sizeof(native_buf);
	if ((lzw = (lzw_t *)Dz1Calloc(sizeof(lzw_t), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&lzw);
		Dz1Thread_printf("Native\n");
		Dz1Thread_tprintb(1, native_buf, native_buf_size, 16);

		fin.ptr = native_buf;
		fin.size = native_buf_size;

		fout.ptr = comp_buf;
		fout.size = 1024;

		lzw_encode(lzw, &fin, &fout, min_code_size);

		comp_size = 1024 - fout.size;

		Dz1Thread_printf("Compressed\n");
		Dz1Thread_tprintb(1, comp_buf, comp_size, 16);
		///////////////////////////////////////////////////////////
		fin.ptr = comp_buf;
		fin.size = comp_size;

		fout.ptr = decomp_buf;
		fout.size = 1024;

		lzw_decode(lzw, &fin, &fout, min_code_size);

		decomp_size = 1024 - fout.size;
		Dz1Thread_printf("Decompressed\n");
		Dz1Thread_tprintb(1, decomp_buf, decomp_size, 16);
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&lzw);
	}
	return err;
}
*/
static bool_t _save_to_bmp(str_t path, str_t name, u32_t seq, u32_t dur_ms, Dz1BMP *bmp, Dz1Error *errp)
{
	Dz1Binary *bin = Dz1Binary_new(NULL, 0, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((sz = Dz1BMP_enc(NULL, -1, bmp, errp)) < 0) ERR_OUT(errp);
		else if ((bin->data = (u8_t *)Dz1Malloc((bin->size = (u32_t)sz), errp)) == NULL) ERR_OUT(errp);
		else if ((sz = Dz1BMP_enc(bin->data, bin->size, bmp, errp)) < 0) ERR_OUT(errp);
		else if (sz != bin->size) ERR_SET_OUT(errp, EFAULT);
		else
		{
			char fn[4096];
			sprintf(fn, "%s_%u.bmp", name, seq);
			if ((*errp = Dz1BinFile_save2(path, fn, bin)).code) ERR_OUT(errp);
			else
			{
				Dz1Error_set(errp, 0);
				Dz1Thread_printf("### BMP File Saved = %s\n", fn);
			}
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return ERR_IS_SUCCESS(errp);
}

typedef struct GifSceneSplitterArg
{
	str_t				 path;
	str_t				 src_name;
	Dz1Gif				*src;
	Dz1BMP				*last;
	u32_t				 seq;
} GifSceneSplitterArg;

static Dz1Error _scene_handler(void *ptr, Dz1GifDataEntry *p)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	GifSceneSplitterArg *arg = (GifSceneSplitterArg *)ptr;
	Dz1Gif *gif = arg->src;
	Dz1GifDescr *descr = gif->descr;

	u32_t dur = 0;
	Dz1BMP *canvas = NULL;
	switch(p->present)
	{
	case Dz1GifDataEntryPresent_graphic:
		if (arg->last == NULL && (arg->last = Dz1BMP_create(descr->width, descr->height, Dz1BMPBPP_colorTrue32, errp)) == NULL) ERR_OUT(errp);
		else if ((canvas = Dz1BMP_create(descr->width, descr->height, Dz1BMPBPP_colorTrue32, errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1BMP_delAndSetNull, (void *)&canvas);
			if ((*errp = Dz1GifUtil_render(gif->descr, p->x.graphic, canvas, arg->last, &dur)).code) ERR_OUT(errp);
			else if (_save_to_bmp(arg->path, arg->src_name, arg->seq, dur, canvas, errp) == FALSE) ERR_OUT(errp);
			else
			{
				arg->seq++;
				Dz1BMP_copyImage(arg->last, canvas);
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1BMP_delAndSetNull, (void *)&canvas);
		}
		break;
	default:
	case Dz1GifDataEntryPresent_app_ext:
	case Dz1GifDataEntryPresent_comment:
		break;
	}
	return err;
}

static Dz1Error gif_test(str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	Dz1Binary *bin = Dz1BinFile_load2(path, name, errp);
	if (bin == NULL) ERR_OUT(errp);
	else
	{
		Dz1Gif *gif = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);

		if ((gif = Dz1Gif_gen(errp)) == NULL) ERR_OUT(errp);
		else
		{
			ssize_t status = 0;
			pthread_cleanup_push(Dz1Gif_delAndSetNull, (void *)&gif);
			if ((status = Dz1Gif_dec(gif, bin->data, bin->size, NULL, errp)) < 0) ERR_OUT(errp);
			else
			{
				Dz1GifDataArr *datas = gif->datas;

				Dz1Thread_printf("Binary Size = %u, decode size = %d\n", bin->size, status);
				if (bin->size - status > 0)
				{
					u8_t *cp = bin->data;
					cp += status;
					Dz1Thread_printf("Remain\n"); Dz1Thread_tprintb(1, cp, 512, 16, FALSE);
				}
				else
				{
					char src_name[1024], *dotp = NULL;
					GifSceneSplitterArg arg = { path, src_name, gif, NULL, 0 };

					strcpy(src_name, name);
					if ((dotp = strrchr(src_name, '.')) != NULL) *dotp = 0;

					if ((*errp = datas->travel(datas, _scene_handler, (void *)&arg)).code) ERR_OUT(errp);
					else Dz1Error_set(errp, 0);
				}
			}
			pthread_cleanup_pop(1); // (Dz1Gif_delAndSetNull, (void *)&gif);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

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

static void _shell_start(void *task)
{	void *sh = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

#ifdef WIN32
	if ((sh = Dz1Shell_new("win32crt", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_gif", &err)) == NULL) Dz1Error_print(&err, 0);
#else
	if ((sh = Dz1Shell_new("xterm", DZ1_SHELL_CMD_ALL, 16, "root", "dz1_gif", &err)) == NULL) ERR_OUT(&err);
#endif
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1Shell_del, (void *)sh);
		if (0) { }
		//else if ((err = Dz1Shell_cmdReg(sh, "{command}", {command_func}, task, "{command description}")).code) ERR_OUT(&err);
		else
		{
			Dz1Shell_start(sh, NULL);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Shell_del, (void *)sh);y
	}
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	Dz1Cleanup_setMemoryExporter(_memoryExport, NULL);
	if ((logfp = fopen("dz1_gif_test.log.txt", "wb")) != NULL)
		Dz1OutputHook_set(_outputHook, NULL);

#ifndef UNIX_SYSTEM
	if (Dz1Socket_init())
	{
#endif
	if (0) { }
	else if ((*errp = gif_test("..\\..\\samples", "sample.gif")).code) ERR_OUT(errp);
	else _shell_start(NULL);


#ifndef UNIX_SYSTEM
	}
	else Dz1Thread_printf("Win sock Initialize Fail\n");
#ifdef _DEBUG
	printf("Press Any Key...\n");
	while(!kbhit()) Sleep(10);
	fflush(stdin);
#endif
#endif
	return err.code;
}

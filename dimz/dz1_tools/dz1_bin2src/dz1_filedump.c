#include <libgen.h>

#include <dz1_malloc.h>
#include <dz1_args.h>
#include <dz1_thread_stdio.h>

static void stream_cancel(void *ptr) { if (ptr) fclose((FILE *)ptr); }
typedef enum DumpMode
{
	DumpMode_hex,
	DumpMode_bin,
} DumpMode;

typedef struct Dz1DumpEnv
{
	bool_t		bHelp;
	DumpMode	mode;
	u32_t		nRow;
	u32_t		nCol;
	bool_t		bChar;
} Dz1DumpEnv;

static str_t help_dumpHelp[] = { "Print this messages", NULL };
static Dz1Error set_dumpHelp(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	env->bHelp = TRUE;
	return err;
}

static str_t help_dumpHex[] = { "dump in Hexdecimal Value", NULL };
static Dz1Error set_dumpHex(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	env->mode = DumpMode_hex;
	return err;
}

static str_t help_dumpBin[] = { "dump in Binary Value", NULL };
static Dz1Error set_dumpBin(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	env->mode = DumpMode_bin;
	return err;
}

static str_t help_setWidth[] = { "set How many bytes in line", "default is 16", NULL };
static Dz1Error set_width(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	if ((env->nCol = atoi(argv[1])) == 0)
	{
		Dz1Thread_printf("Width = [%s]\n", argv[1]);
		ERR_SET_OUT(&err, EINVAL);
	}
	return err;
}

static str_t help_setHeight[] = { "set How many line in block", "default is 16", NULL };
static Dz1Error set_height(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	if ((env->nRow = atoi(argv[1])) == 0)
	{
		Dz1Thread_printf("Height = [%s]\n", argv[1]);
		ERR_SET_OUT(&err, EINVAL);
	}
	return err;
}

static str_t help_setChar[] = { "Dump additional letters", NULL };
static Dz1Error set_char(void *userEnv, str_t baseName, int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1DumpEnv *env = (Dz1DumpEnv *)userEnv;
	env->bChar = TRUE;
	return err;
}

static Dz1Args opts[] =
{
	{ "-help", __DZ1VAL(1), set_dumpHelp, help_dumpHelp },
	{ "-H", __DZ1VAL(1), set_dumpHex, help_dumpHex },
	{ "-B", __DZ1VAL(1), set_dumpBin, help_dumpBin},
	{ "-w", __DZ1VAL(2), set_width, help_setWidth },
	{ "-h", __DZ1VAL(2), set_height, help_setHeight },
	{ "-c", __DZ1VAL(1), set_char, help_setChar},
	Dz1ArgsTermEntry
};

static void dumpByteBin(u8_t c)
{
	u8_t mask;
	char temp[9], *cp = temp;
	for (mask = 0x80; mask; mask = mask >> 1)
		if (c & mask) *cp++ = '1'; else *cp++ = '0';
	*cp = '\0';
	Dz1Thread_printf("%s ", temp);
}

static void dumpByte(u8_t c, DumpMode mode)
{
	switch(mode)
	{
		case DumpMode_hex:
			Dz1Thread_printf("%02X ", c);
			break;
		case DumpMode_bin:
			dumpByteBin(c);
			break;
	}
}

static void dumpByteDummy(DumpMode mode)
{
	switch(mode)
	{
		case DumpMode_hex:
			Dz1Thread_printf("   ");
			break;
		case DumpMode_bin:
			Dz1Thread_printf("         ");
			break;
	}
}

static void _dump(u32_t offset, u8_t *data, size_t size, size_t fullSize, DumpMode mode, bool_t bChar)
{
	size_t _size = size;
	u8_t *cp = data;
	Dz1Thread_printf("%08X : ", offset);
	while(size) { dumpByte(*cp++, mode); size--; fullSize--; }
	if (bChar)
	{
		while(fullSize) { dumpByteDummy(mode); fullSize--; }

		Dz1Thread_printf(": ");

		cp = data;
		while(_size) { Dz1Thread_printf("%c", *cp <= 0x20 || *cp & 0x80 ? '.' : *cp++); _size--; }
	}
	Dz1Thread_printf("\n");
}

static void dump(u32_t offset, u8_t *data, size_t size, u32_t width, DumpMode mode, bool_t bChar)
{
	size_t psize;
	u8_t *cp = data;
	while(size)
	{
		if (size > width) psize = width; else psize = size;
		_dump(offset, cp, psize, width, mode, bChar);
		offset += psize;
		cp += psize;
		size -= psize;
	}
}

int main(int argc, char *argv[])
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1DumpEnv env = { FALSE, DumpMode_hex, 16, 16, FALSE };
	Dz1Param *param = Dz1Param_new(argc - 1, &argv[1], &err);
	if (param == NULL) ERR_OUT(&err);
	else
	{
		char myname[1024], *myName;

		pthread_cleanup_push((Dz1DelFunc)Dz1Param_del, (void *)param);

		strcpy(myname, argv[0]);
		myName = basename(myname);
		if ((err = Dz1Param_proc(param, opts, myName, &env)).code)
		{
			ERR_OUT(&err);
			Dz1Args_help(opts, argv[0], "file", 0);
		}
		else if (param->argc != 1)
		{
			Dz1Thread_printf("Invalid filename...\n");
			Dz1Args_help(opts, myName, "file", 0);
		}
		else if (env.bHelp) Dz1Args_help(opts, myName, "file", 0);
		else
		{
			size_t blockSize = env.nRow * env.nCol;
			u8_t *block = (u8_t *)Dz1Malloc(blockSize, &err);
			if (block == NULL) ERR_OUT(&err);
			else
			{
				FILE *fp = NULL;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)block);

				if ((fp = fopen(param->argv[0], "rb")) == NULL) ERR_SET_OUT(&err, errno);
				else
				{
					unsigned int offset = 0;
					size_t readSize;
					pthread_cleanup_push(stream_cancel, fp);

					do
					{
						if ((readSize = fread(block, 1, blockSize, fp)) == 0)
						{
							int status;
							if (feof(fp)) break;
							else if ((status = ferror(fp)) != 0) ERR_SET_OUT(&err, status);
							else ERR_SET_OUT(&err, EFAULT);
						}
						else
						{
							dump(offset, block, readSize, env.nCol, env.mode, env.bChar);
							Dz1Thread_printf("\n");
						}
						offset += readSize;
					} while(err.code == 0);
					pthread_cleanup_pop(1); // (stream_cancel, fp);
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)block);
			}
		}
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1Param_del, (void *)param);
	}
	return err.code;
}

#include <dz1_stdio.h>
#include "dz1_file2src_data_util.h"
#include "dz1_file2src_arg_util.h"

u32_t __avoid_no_symbol_warning_dz1_file2src_arg_util_c_ = 0;
/*
Dz1Error Dz1File2Src_publishData8(FILE *dstfp, File2SrcArgDst *dst, FILE *srcfp, File2SrcArgSrc *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u8_t c = 0;
	int tab = 0;
	u32_t cnt = 0;

	while(fread(&c, sizeof(u8_t), 1, srcfp) == 1)
	{
		if (cnt == 0) { pTAB(dstfp, tab); fprintf(dstfp, "0x%02X, ", c); }
		else fprintf(dstfp, "0x%02X, ", c);
		cnt++;

		if (cnt % dst->value_per_line == 0) { pCRLF(dstfp, dst->mode); cnt = 0; }
	}

	return err;
}

Dz1Error Dz1File2Src_publishData16(FILE *dstfp, File2SrcArgDst *dst, FILE *srcfp, File2SrcArgSrc *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u16_t c = 0;
	int tab = 0;
	u32_t cnt = 0;

	while(_read2Byte(srcfp, &c, &err) > 0)
	{
		if (cnt == 0) { pTAB(dstfp, tab); fprintf(dstfp, "0x%04X, ", c); }
		else fprintf(dstfp, "0x%04X, ", c);
		cnt++;

		if (cnt % dst->value_per_line == 0) { pCRLF(dstfp, dst->mode); cnt = 0; }
	}

	return err;
}

Dz1Error Dz1File2Src_publishData32(FILE *dstfp, File2SrcArgDst *dst, FILE *srcfp, File2SrcArgSrc *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u32_t c = 0;
	int tab = 0;
	u32_t cnt = 0;

	while(_read4Byte(srcfp, &c, &err) > 0)
	{
		if (cnt == 0) { pTAB(dstfp, tab); fprintf(dstfp, "0x%08X, ", c); }
		else fprintf(dstfp, "0x%08X, ", c);
		cnt++;

		if (cnt % dst->value_per_line == 0) { pCRLF(dstfp, dst->mode); cnt = 0; }
	}

	return err;
}

Dz1Error Dz1File2Src_publishData64(FILE *dstfp, File2SrcArgDst *dst, FILE *srcfp, File2SrcArgSrc *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	u64_t c = 0;
	int tab = 0;
	u32_t cnt = 0;

	while(_read8Byte(srcfp, &c, &err) > 0)
	{
		if (cnt == 0) { pTAB(dstfp, tab); fprintf(dstfp, "0x%16llX, ", c); }
		else fprintf(dstfp, "0x%16llX, ", c);
		cnt++;

		if (cnt % dst->value_per_line == 0) { pCRLF(dstfp, dst->mode); cnt = 0; }
	}

	return err;
}

static Dz1Error Dz1File2SrcData_readTextByLine(Dz1File2SrcData *dst, str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	char fn[4096];

	sprintf(fn, "%s" DIR_SEPRATOR "%s", path, name);

	if ((fp = fopen(fn, "rb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		u8_t *buf = NULL;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		if ((buf = (u8_t *)Dz1Malloc(8192, &err)) == NULL) ERR_OUT(&err);
		else
		{
			u32_t len = 0;
			u8_t *cp = buf, c;
			Dz1File2SrcDataEntry *node = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
			while(err.code == 0 && fread(&c, sizeof(char), 1, fp) == 1)
			{
				if (c == '\r') continue;
				else if (c == '\n')
				{
					*cp++ = '\0'; len++;
					// Make node and add
					if ((err = Dz1File2SrcData_addBlock(dst, buf, len)).code) ERR_OUT(&err);
					cp = buf; len = 0;
				}
				else { *cp++ = c; len++; }
			}

			if (cp != buf)
			{
				*cp++ = '\0'; len++;
				// Make node and add
				if ((err = Dz1File2SrcData_addBlock(dst, buf, len)).code) ERR_OUT(&err);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readTextByBlock(Dz1File2SrcData *dst, str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	char fn[4096];

	sprintf(fn, "%s" DIR_SEPRATOR "%s", path, name);

	if ((fp = fopen(fn, "rb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		u8_t *line = NULL;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		if ((line = (u8_t *)Dz1Malloc(8192, &err)) == NULL) ERR_OUT(&err);
		else
		{
			u8_t *buf = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)line);
			if ((buf = (u8_t *)Dz1Malloc(65535, &err)) == NULL) ERR_OUT(&err);
			else
			{
				u32_t len = 0;
				u8_t *cp = line, *dp = buf, c;
				Dz1File2SrcDataEntry *node = NULL;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
				while(err.code == 0 && fread(&c, sizeof(char), 1, fp) == 1)
				{
					if (c == '\r') { *dp++ = c; len++;}
					else if (c == '\n')
					{
						*cp++ = '\0';
						*dp++ = c; len++;
						// Make node and add
						if (strlen(line) == 0)
						{
							*dp++ = '\0'; len++;
							if ((err = Dz1File2SrcData_addBlock(dst, buf, len)).code) ERR_OUT(&err);
							dp = buf; len = 0; cp = line;
						}
					}
					else { *cp++ = *dp++ = c; len++; }
				}

				if (cp != line)
				{
					*cp++ = '\0';
					*dp++ = '\0'; len++;
					// Make node and add
					if ((err = Dz1File2SrcData_addBlock(dst, buf, len)).code) ERR_OUT(&err);
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)line);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readText(Dz1File2SrcData *dst, str_t path, str_t name, File2SrcArrayOpt arrayOpt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcDataEntry *node = NULL;
	switch(arrayOpt)
	{
	case File2SrcArrayOpt_SingleVar:
		if ((node = Dz1File2SrcDataEntry_new(NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			char fn[4096];
			pthread_cleanup_push(Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
			sprintf(fn, "%s" DIR_SEPRATOR "%s", path, name);
			if ((node->block = Dz1BinFile_load(fn, &err)) == NULL) ERR_OUT(&err);
			else if ((err = dst->list->add(dst->list, node)).code) ERR_OUT(&err);
			else node = NULL;
			pthread_cleanup_pop(1); // (Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
		}
		break;
	case File2SrcArrayOpt_ArrayByLine:
		if ((err = Dz1File2SrcData_readTextByLine(dst, path, name)).code) ERR_OUT(&err);
		break;
	case File2SrcArrayOpt_ArrayByBlock:
		if ((err = Dz1File2SrcData_readTextByBlock(dst, path, name)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readHex(Dz1File2SrcData *dst, str_t path, str_t name, File2SrcArrayOpt arrayOpt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcDataEntry *node = NULL;
	switch(arrayOpt)
	{
	case File2SrcArrayOpt_SingleVar:
		if ((node = Dz1File2SrcDataEntry_new(NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			char fn[4096];
			pthread_cleanup_push(Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
			sprintf(fn, "%s" DIR_SEPRATOR "%s", path, name);
			if ((node->block = Dz1BinFile_load(fn, &err)) == NULL) ERR_OUT(&err);
			else if ((err = dst->list->add(dst->list, node)).code) ERR_OUT(&err);
			else node = NULL;
			pthread_cleanup_pop(1); // (Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
		}
		break;
	case File2SrcArrayOpt_ArrayByLine:
		if ((err = Dz1File2SrcData_readHexByLine(dst, path, name)).code) ERR_OUT(&err);
		break;
	case File2SrcArrayOpt_ArrayByBlock:
		if ((err = Dz1File2SrcData_readHexByBlock(dst, path, name)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

Dz1Error Dz1File2SrcData_read(Dz1File2SrcData *dst, File2SrcArgSrc *src, File2SrcArrayOpt arrayOpt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(src->type)
	{
	case File2SrcTypeSrc_PlaneText:
		if ((err = Dz1File2SrcData_readText(dst, src->path, src->name, arrayOpt)).code) ERR_OUT(&err);
		break;
	case File2SrcTypeSrc_HexDump:
		if ((err = Dz1File2SrcData_readHex(dst, src->path, src->name, arrayOpt)).code) ERR_OUT(&err);
		break;
	case File2SrcTypeSrc_Binary:
		if ((err = Dz1File2SrcData_readText(dst, src->path, src->name, File2SrcArrayOpt_SingleVar)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}
*/

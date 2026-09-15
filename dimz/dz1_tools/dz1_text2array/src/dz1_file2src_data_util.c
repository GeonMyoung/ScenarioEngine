#include <dz1.h>
#include <ctype.h>

#include "dz1_file2src_data_util.h"

typedef Dz1Error (*DataProcessFunc)(Dz1File2SrcData *dst, u8_t *data, u32_t size, File2SrcConvArg *arg);

#define DZ1FILE2SRC_DEF_PREFIX			"DZ1_FILE2SRC"
static str_t GetDefineName(char dst[1024], str_t prefix, str_t src, Dz1Error *errp)
{
	char c, *dp = dst;
	int i, len = (int)strlen(src);
	bool_t prevLetterIsUpperCase = TRUE;

	strcpy(dp, prefix); dp += strlen(prefix);
	*dp++ = '_';

	for (i = 0; i < len; i++)
	{
		c = src[i];
		if (c >= 'a' && c <= 'z')
		{
			prevLetterIsUpperCase = FALSE;
			c = (c - 'a') + 'A';
		}
		else if (c >= 'A' && c <= 'Z')
		{
			if (prevLetterIsUpperCase == FALSE) *dp++ = '_';
			prevLetterIsUpperCase = TRUE;
		}
		else if (c >= '0' && c <= '9')
		{
			prevLetterIsUpperCase = TRUE;
		}
		else
		{
			ERR_SET_OUT(errp, EINVAL);
			return NULL;;
		}
		*dp++ = c;
	}
	*dp++ = '\0';
	return dst;
}

static void pTAB(FILE *fp, int tab) { while(tab--) fprintf(fp, "\t"); }
static void pCRLF(FILE *fp, File2SrcOutputMode mode)
{
	switch(mode)
	{
	default:
	case File2SrcOutputMode_DOS:
		fprintf(fp, "\r");
	case File2SrcOutputMode_UNIX:
		fprintf(fp, "\n");
		break;
	}
}

static Dz1Error Dz1File2SrcData_addBlock(Dz1File2SrcData *dst, u8_t *buf, u32_t len)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1File2SrcDataEntry *node = NULL;
	if ((node = Dz1File2SrcDataEntry_new(NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);

		if ((node->block = Dz1Binary_new(buf, len, &err)) == NULL) ERR_OUT(&err);
		else if ((err = dst->list->add(dst->list, node)).code) ERR_OUT(&err);
		else node = NULL;

		pthread_cleanup_pop(1); // (Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readBinary(Dz1File2SrcData *dst, str_t path, str_t name)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcDataEntry *node = NULL;
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
	return err;
}

static Dz1Error Dz1File2SrcData_readTextByLine(Dz1File2SrcData *dst, DataProcessFunc dataProc, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	char fn[4096];

	sprintf(fn, "%s" DIR_SEPRATOR "%s", arg->srcPath, arg->srcName);

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
			//Dz1File2SrcDataEntry *node = NULL;
			pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
			while(err.code == 0 && fread(&c, sizeof(char), 1, fp) == 1)
			{
				if (c == '\r') continue;
				else if (c == '\n')
				{
					*cp++ = '\0'; len++;
					// Make node and add
					if ((err = dataProc(dst, buf, len, arg)).code) ERR_OUT(&err);
					else { cp = buf; len = 0; }
				}
				else { *cp++ = c; len++; }
			}

			if (cp != buf)
			{
				*cp++ = '\0'; len++;
				// Make node and add
				if ((err = dataProc(dst, buf, len, arg)).code) ERR_OUT(&err);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readTextByBlock(Dz1File2SrcData *dst, DataProcessFunc dataProc, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	FILE *fp = NULL;
	char fn[4096];

	sprintf(fn, "%s" DIR_SEPRATOR "%s", arg->srcPath, arg->srcName);

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
				//Dz1File2SrcDataEntry *node = NULL;
				pthread_cleanup_push(Dz1Memory_cancel, (void *)buf);
				while(err.code == 0 && fread(&c, sizeof(char), 1, fp) == 1)
				{
					if (c == '\r') { *dp++ = c; len++;}
					else if (c == '\n')
					{
						*cp++ = '\0'; cp = line;
						*dp++ = c; len++;
						// Make node and add
						if (strlen((char *)line) == 0)
						{
							*dp++ = '\0';
							if ((err = dataProc(dst, buf, len, arg)).code) ERR_OUT(&err);
							dp = buf; len = 0;
						}
					}
					else { *cp++ = *dp++ = c; len++; }
				}

				if (cp != line)
				{
					*cp++ = '\0';
					*dp++ = '\0'; len++;
					// Make node and add
					if ((err = dataProc(dst, buf, len, arg)).code) ERR_OUT(&err);
				}
				pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)buf);
			}
			pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)line);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static Dz1Error _addDataEntry(Dz1File2SrcData *dst, u8_t *buf, u32_t size, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((err = Dz1File2SrcData_addBlock(dst, buf, size)).code) ERR_OUT(&err);
	return err;
}

static Dz1Error Dz1File2SrcData_readTextPlaneText(Dz1File2SrcData *dst, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *_opt = arg->opt;
	File2SrcConvTextOpt *opt = _opt->x.textMode;
	//Dz1File2SrcDataEntry *node = NULL;
	switch(opt->form)
	{
	case File2SrcVariableForm_SingleVariable:
		if ((err = Dz1File2SrcData_readBinary(dst, arg->srcPath, arg->srcName)).code) ERR_OUT(&err);
		break;
	case File2SrcVariableForm_ArrayByLine:
		if ((err = Dz1File2SrcData_readTextByLine(dst, _addDataEntry, arg)).code) ERR_OUT(&err);
		break;
	case File2SrcVariableForm_ArrayByBlock:
		if ((err = Dz1File2SrcData_readTextByBlock(dst, _addDataEntry, arg)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

static ssize_t _getWord(char temp[1024], u32_t *len, u8_t *src, u32_t size, Dz1Error *err)
{
	if (size == 0) return 0;
	else
	{
		u8_t *dp = (u8_t *)temp, *cp = src;

		size = size > 1023 ? 1023 : size;

		while(size > 0 && *cp != '\0' && isspace((int)(*cp) & 0xFF)) { cp++; size--; }	// trim white space

		while(size > 0 && *cp != '\0' && !isspace((int)(*cp) & 0xFF)) { *dp++ = *cp++; size--; (*len)++; } // copy letters
		*dp = '\0';

		return (ssize_t)(cp - src);
	}
}

static ssize_t _getValue(char *dst, char src[1024], u32_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (size > 0)
	{
		char *cp = src;
		if (size > 2 && src[0] == '0' && src[1] == 'x') { cp = &src[2]; size -= 2; ret += 2; }

		if (size == 0) { ERR_SET_OUT(errp, ENOMEM); return FALSE; }
		else
		{
			u8_t t = 0;
			size = size > 2 ? 2 : size;
			while(size)
			{
				t = t << 4;
				if (*cp >= 'a' && *cp <= 'f') t = t | ((*cp) - 'a' + 10);
				else if (*cp >= 'A' && *cp <= 'F') t = t | ((*cp) - 'A' + 10);
				else if (*cp >= '0' && *cp <= '9') t = t | ((*cp) - '0');
				else { ret = FALSE; break; }
				cp++; size--; ret++;
			}
			(*dst) = t;
		}
	}
	return ret;
}

static ssize_t _dataConvert(u8_t *dst, size_t dstSize, u8_t *src, u32_t srcSize, Dz1Error *errp)
{
	ssize_t status;
	char temp[1024], *tp;
	u8_t *cp = src, v;
	u32_t cnt = 0, len;
	while ((status = _getWord(temp, &len, cp, srcSize, errp)) > 0)
	{
		cp += status; srcSize -= (u32_t)status;
		tp = temp;

		while((status = _getValue((char *)&v, tp, len, errp)) > 0)
		{
			cnt++;
			tp += status;
			len -= (u32_t)status;
			if (dst) *dst++ = v;
		}
	}
	return (ssize_t)cnt;
}

static Dz1Error _parseAndAdd(Dz1File2SrcData *dst, u8_t *buf, u32_t size, File2SrcConvArg *arg)
{
	ssize_t cnt = 0, _cnt;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcDataEntry *node = NULL;
	if ((cnt = _dataConvert(NULL, -1, buf, size, &err)) < 0) ERR_OUT(&err);
	else if ((node = Dz1File2SrcDataEntry_new(NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1Binary *b = NULL;
		pthread_cleanup_push(Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
		if ((node->block = b = Dz1Binary_new(DZ1_BIN_DATA_ALLOC, (u32_t)cnt, &err)) == NULL) ERR_OUT(&err);
		else if ((_cnt = _dataConvert(b->data, b->size, buf, size, &err)) < 0) ERR_OUT(&err);
		else if (_cnt != cnt) ERR_SET_OUT(&err, EFAULT);
		else if ((err = dst->list->add(dst->list, node)).code) ERR_OUT(&err);
		else node = NULL;
		pthread_cleanup_pop(1); // (Dz1File2SrcDataEntry_delAndSetNull, (void *)&node);
	}
	return err;
}

static Dz1Error _parseEntireFile(Dz1File2SrcData *dst, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	char fn[4096];
	Dz1Binary *bin = NULL;
	sprintf(fn, "%s" DIR_SEPRATOR "%s", arg->srcPath, arg->srcName);

	if ((bin = Dz1BinFile_load(fn, &err)) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((err = _parseAndAdd(dst, bin->data, bin->size, arg)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readTextHexDump(Dz1File2SrcData *dst, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *_opt = arg->opt;
	File2SrcConvTextOpt *opt = _opt->x.textMode;
	//Dz1File2SrcDataEntry *node = NULL;
	switch(opt->form)
	{
	case File2SrcVariableForm_SingleVariable:
		if ((err = _parseEntireFile(dst, arg)).code) ERR_OUT(&err);
		break;
	case File2SrcVariableForm_ArrayByLine:
		if ((err = Dz1File2SrcData_readTextByLine(dst, _parseAndAdd, arg)).code) ERR_OUT(&err);
		break;
	case File2SrcVariableForm_ArrayByBlock:
		if ((err = Dz1File2SrcData_readTextByBlock(dst, _parseAndAdd, arg)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

static Dz1Error Dz1File2SrcData_readText(Dz1File2SrcData *dst, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *_opt = arg->opt;
	File2SrcConvTextOpt *opt = _opt->x.textMode;
	File2SrcConvTextAttr *attr = opt->attr;
	switch(attr->present)
	{
	case File2SrcConvTextAttrPresent_PlaneText:
		if ((err = Dz1File2SrcData_readTextPlaneText(dst, arg)).code) ERR_OUT(&err);
		break;
	case File2SrcConvTextAttrPresent_HexDump:
		if ((err = Dz1File2SrcData_readTextHexDump(dst, arg)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

Dz1Error Dz1File2SrcData_read(Dz1File2SrcData *dst, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *opt = arg->opt;
	switch(opt->present)
	{
	case File2SrcConvOptPresent_textMode:
		if ((err = Dz1File2SrcData_readText(dst, arg)).code) ERR_OUT(&err);
		break;
	case File2SrcConvOptPresent_binMode:
		if ((err = Dz1File2SrcData_readBinary(dst, arg->srcPath, arg->srcName)).code) ERR_OUT(&err);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

///////////////////////////////////////////////////////////////////////////////
// Publish
///////////////////////////////////////////////////////////////////////////////
static bool_t _isArrayPublish(File2SrcConvOpt *opt)
{
	if (opt->present == File2SrcConvOptPresent_binMode) return FALSE;
	else
	{
		File2SrcConvTextOpt *tOpt = opt->x.textMode;
		if (tOpt->form == File2SrcVariableForm_SingleVariable) return FALSE;
		else return TRUE;
	}
}

Dz1Error Dz1File2Src_publishHdr(Dz1File2SrcData *src, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	char fn[4096];
	FILE *fp = NULL;

	sprintf(fn, "%s" DIR_SEPRATOR "%s.h", arg->dstPath, arg->dstName);

	if ((fp = fopen(fn, "wb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		int tab = 0;
		char defName[1024];
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		GetDefineName(defName, DZ1FILE2SRC_DEF_PREFIX, arg->var_name, NULL);
		pTAB(fp, 0); fprintf(fp, "#ifndef %s", defName); pCRLF(fp, arg->mode);
		pTAB(fp, 0); fprintf(fp, "#define %s", defName); pCRLF(fp, arg->mode);
		pCRLF(fp, arg->mode);
		pTAB(fp, 0); fprintf(fp, "#ifdef __cplusplus"); pCRLF(fp, arg->mode);
		pTAB(fp, 0); fprintf(fp, "#extern \"C\" {"); pCRLF(fp, arg->mode);
		pTAB(fp, 0); fprintf(fp, "#endif // __cplusplus"); pCRLF(fp, arg->mode);
		pTAB(fp, 0); pCRLF(fp, arg->mode);
		pTAB(fp, 0); fprintf(fp, "extern unsigned char *%s%s", _isArrayPublish(arg->opt) ? "*" : "",	arg->var_name); pCRLF(fp, arg->mode);
		pTAB(fp, 0); pCRLF(fp, arg->mode);
		pTAB(fp, tab); fprintf(fp, "#ifdef __cplusplus"); pCRLF(fp, arg->mode);
		pTAB(fp, tab); fprintf(fp, "}"); pCRLF(fp, arg->mode);
		pTAB(fp, tab); fprintf(fp, "#endif // __cplusplus"); pCRLF(fp, arg->mode);
		pTAB(fp, tab); fprintf(fp, "#endif // %s", defName); pCRLF(fp, arg->mode);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

static void Dz1File2Src_publishSrcDataStr(FILE *fp, str_t src, u32_t size, File2SrcOutputMode mode, int tab)
{
	u32_t lineLen = 0;
//	pTAB(fp, tab);
	fprintf(fp, "Dz1T(\"");
	while(*src != '\0' && size)
	{
		size--;
		if (*src == '\r') { fprintf(fp, "\\r"); lineLen++; }
		else if (*src == '\"') { fprintf(fp, "\\\""); lineLen += 2; }
		else if (*src == '\\') { fprintf(fp, "\\\\"); lineLen += 2; }
		else if (*src == '\n')
		{
			fprintf(fp, "\\n\")"); lineLen = 0;
			if (size)
			{
				pCRLF(fp, mode);
//				pTAB(fp, tab);
				fprintf(fp, "Dz1T(\"");
			}
		}
		else
		{
			fprintf(fp, "%c", *src);
			lineLen++;
		}
		src++;
	}
	if (lineLen) fprintf(fp, "\")");
}

static void Dz1File2Src_publishSrcDataBinLine(FILE *fp, u8_t *cp, u32_t size)
{
	fprintf(fp, "0x%02X", *cp++); size--;
	while(size--) fprintf(fp, ", 0x%02X", *cp++);
}

static void Dz1File2Src_publishSrcDataBin(FILE *fp, Dz1Binary *src, File2SrcOutputMode mode, int tab)
{
	u8_t *cp = src->data;
	u32_t size = src->size;
	pTAB(fp, tab++); fprintf(fp, "{"); pCRLF(fp, mode);
	while(size > 16)
	{
		pTAB(fp, tab); Dz1File2Src_publishSrcDataBinLine(fp, cp, 16); fprintf(fp, ","); pCRLF(fp, mode);
		size -= 16;
		cp += 16;
	}
	if (size) { pTAB(fp, tab); Dz1File2Src_publishSrcDataBinLine(fp, cp, size); pCRLF(fp, mode); }
	pTAB(fp, --tab); fprintf(fp, "}");
}

static Dz1Error Dz1File2Src_publishSrcData(FILE *fp, Dz1Binary *src, File2SrcConvTextPublish publish, File2SrcOutputMode mode, int tab)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	switch(publish)
	{
	case File2SrcConvTextPublish_String:
		Dz1File2Src_publishSrcDataStr(fp, (str_t)src->data, src->size, mode, tab);
		break;
	case File2SrcConvTextPublish_Binary:
		Dz1File2Src_publishSrcDataBin(fp, src, mode, tab);
		break;
	default:
		ERR_SET_OUT(&err, EINVAL);
		break;
	}
	return err;
}

typedef struct PublishSrcArg
{
	FILE *fp;
	str_t var_name;
	File2SrcConvTextPublish publish;
	File2SrcOutputMode mode;
	bool_t hdrMode;
	int tab;
	u32_t cnt;
} PublishSrcArg;

static Dz1Error _Dz1File2Src_publishSrcBinElement(void *ptr, Dz1File2SrcDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSrcArg *arg = (PublishSrcArg *)ptr;

	if (p->block->size > 0)
	{
		pTAB(arg->fp, arg->tab); fprintf(arg->fp, "%sunsigned char *%s%u =", arg->hdrMode ? "static __inline__ " : "", arg->var_name, arg->cnt++); pCRLF(arg->fp, arg->mode);
		if ((err = Dz1File2Src_publishSrcData(arg->fp, p->block, File2SrcConvTextPublish_Binary, arg->mode, arg->tab)).code) ERR_OUT(&err);
		else { fprintf(arg->fp, ";"); pCRLF(arg->fp, arg->mode); }
	}
	return err;
}

static Dz1Error _Dz1File2Src_publishSrcBinArray(void *ptr, Dz1File2SrcDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	PublishSrcArg *arg = (PublishSrcArg *)ptr;

	if (p->block->size > 0)
	{
		pTAB(arg->fp, arg->tab); fprintf(arg->fp, "%s%u,", arg->var_name, arg->cnt++); pCRLF(arg->fp, arg->mode);
	}
	return err;
}

static Dz1Error _Dz1File2Src_publishSrcStrArray(void *ptr, Dz1File2SrcDataEntry *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	PublishSrcArg *arg = (PublishSrcArg *)ptr;

	if ((err = Dz1File2Src_publishSrcData(arg->fp, p->block, arg->publish, arg->mode, arg->tab)).code) ERR_OUT(&err);
	else { fprintf(arg->fp, ","); pCRLF(arg->fp, arg->mode); }

	return err;
}

static Dz1Error _Dz1File2Src_publishSrc(FILE *fp, Dz1File2SrcData *src, str_t var_name,
										File2SrcVariableForm form, File2SrcConvTextPublish publish,
										File2SrcOutputMode mode, int tab, bool_t hdrMode)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (form == File2SrcVariableForm_SingleVariable)
	{
		Dz1File2SrcDataEntry *single = src->list->getHead(src->list);
		if (single == NULL) ERR_SET_OUT(&err, EFAULT);
		else
		{
			pTAB(fp, tab); fprintf(fp, "%sunsigned char *%s =", hdrMode ? "static __inline__ " : "", var_name); pCRLF(fp, mode);
			if ((err = Dz1File2Src_publishSrcData(fp, single->block, publish, mode, tab)).code) ERR_OUT(&err);
			else { fprintf(fp, ";"); pCRLF(fp, mode); }
		}
	}
	else
	{	// Array Variable
		PublishSrcArg _arg = { fp, var_name, publish, mode, hdrMode, 0, 0 };
		if (publish == File2SrcConvTextPublish_Binary)
		{	// Publish Binary Element Data
			_arg.tab = tab;
			_arg.cnt = 0;
			if ((err = src->list->travel(src->list, _Dz1File2Src_publishSrcBinElement, (void *)&_arg)).code) ERR_OUT(&err);
		}

		pTAB(fp, tab++); fprintf(fp, "%sunsigned char *%s[] = {", hdrMode ? "static __inline__ " : "", var_name); pCRLF(fp, mode);

		if (publish == File2SrcConvTextPublish_Binary)
		{
			_arg.tab = tab;
			_arg.cnt = 0;
			if ((err = src->list->travel(src->list, _Dz1File2Src_publishSrcBinArray, (void *)&_arg)).code) ERR_OUT(&err);
			pTAB(fp, tab); fprintf(fp, "NULL"); pCRLF(fp, mode);
		}
		else
		{
			_arg.tab = tab;
			_arg.cnt = 0;
			if ((err = src->list->travel(src->list, _Dz1File2Src_publishSrcStrArray, (void *)&_arg)).code) ERR_OUT(&err);
			fprintf(fp, "NULL"); pCRLF(fp, mode);
		}
		pTAB(fp, --tab); fprintf(fp, "};"); pCRLF(fp, mode);
	}
	return err;
}

Dz1Error Dz1File2Src_publishSrc(Dz1File2SrcData *src, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *opt = arg->opt;

	char fn[4096];
	FILE *fp = NULL;

	sprintf(fn, "%s" DIR_SEPRATOR "%s.c", arg->dstPath, arg->dstName);

	if ((fp = fopen(fn, "wb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		int tab = 0;
		File2SrcVariableForm form = File2SrcVariableForm_SingleVariable;
		File2SrcConvTextPublish publish = File2SrcConvTextPublish_Binary;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		pTAB(fp, tab); fprintf(fp, "#include \"%s.h\"", arg->dstName); pCRLF(fp, arg->mode);
		pTAB(fp, tab); pCRLF(fp, arg->mode);

		if(opt->present == File2SrcConvOptPresent_textMode)
		{
			File2SrcConvTextOpt *tOpt = opt->x.textMode;
			File2SrcConvTextAttr *attr = tOpt->attr;

			form = tOpt->form;
			if (attr->present == File2SrcConvTextAttrPresent_PlaneText)
				publish = attr->x.PlaneText;
		}

		if ((err = _Dz1File2Src_publishSrc(fp, src, arg->var_name, form, publish, arg->mode, tab, FALSE)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

Dz1Error Dz1File2Src_publishHdrStatic(Dz1File2SrcData *src, File2SrcConvArg *arg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	File2SrcConvOpt *opt = arg->opt;

	char fn[4096];
	FILE *fp = NULL;

	sprintf(fn, "%s" DIR_SEPRATOR "%s.h", arg->dstPath, arg->dstName);

	if ((fp = fopen(fn, "wb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		int tab = 0;
		char defName[1024];
		File2SrcVariableForm form = File2SrcVariableForm_SingleVariable;
		File2SrcConvTextPublish publish = File2SrcConvTextPublish_Binary;

		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		GetDefineName(defName, DZ1FILE2SRC_DEF_PREFIX, arg->var_name, NULL);
		pTAB(fp, tab); fprintf(fp, "#ifndef %s", defName); pCRLF(fp, arg->mode);
		pTAB(fp, tab); fprintf(fp, "#define %s", defName); pCRLF(fp, arg->mode);

		pCRLF(fp, arg->mode);
		if(opt->present == File2SrcConvOptPresent_textMode)
		{
			File2SrcConvTextOpt *tOpt = opt->x.textMode;
			File2SrcConvTextAttr *attr = tOpt->attr;

			form = tOpt->form;
			if (attr->present == File2SrcConvTextAttrPresent_PlaneText)
				publish = attr->x.PlaneText;
		}
		pCRLF(fp, arg->mode);

		if ((err = _Dz1File2Src_publishSrc(fp, src, arg->var_name, form, publish, arg->mode, tab, TRUE)).code) ERR_OUT(&err);

		pTAB(fp, tab); fprintf(fp, "#endif // %s", defName); pCRLF(fp, arg->mode);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

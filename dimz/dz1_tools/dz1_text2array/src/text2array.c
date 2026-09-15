#include <dz1_text2array.h>
#include <dz1_stdio.h>

static bool_t isEscapedLetter(char c)
{
	switch(c)
	{
	case '\\':
	case '\"':
		return TRUE;
	default:
		return FALSE;
	}
}

static void writeText(FILE *dst, str_t src, str_t crlf)
{
	char *cp = src;
	fputc('\"', dst);
	while(*cp)
	{
		if (isEscapedLetter(*cp))
			fputc('\\', dst);
		fputc(*cp, dst);
		cp++;
	}
	fprintf(dst, "\",%s", crlf);
}

Dz1Error dz1_text2array(str_t srcFileName, str_t dstFileName, str_t varName, bool_t isStatic, bool_t isUNIX)
{
	FILE *fSrc = NULL, *fDst = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((fSrc = fopen(srcFileName, "rb")) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fSrc);
		if ((fDst = fopen(dstFileName, "wb")) == NULL) ERR_SET_OUT(&err, errno);
		else
		{
			ssize_t status;
			u8_t buf[65535];
			str_t crlf = isUNIX ? "\n" : "\r\n";
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)fDst);
			fprintf(fDst, "%sstr_t %s[] = {%s", isStatic ? "static " : "", varName, crlf);
			while((status = _readLine(fSrc, buf, 65535, &err)) > 0)
				//fprintf(fDst, "\"%s\",%s", buf, crlf);
				writeText(fDst, buf, crlf);
			fprintf(fDst, "NULL%s", crlf);
			fprintf(fDst, "};%s", crlf);
			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fDst);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fSrc);
	}
	return err;
}
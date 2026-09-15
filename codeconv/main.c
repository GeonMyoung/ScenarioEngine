#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <codeconv.h>

void binLineDump(FILE *fp, unsigned char *data,unsigned int length)
{
	unsigned int i;
	for (i = 0; i < length; i++)
		fprintf(fp, "%02x ",data[i]);
	if (length < 16)
		for (i = length; i < 16; i++)
			fprintf(fp, "   ");
	fprintf(fp, "  ");
	for (i = 0; i < length; i++)
		fprintf(fp, "%c",data[i] < 32 || (data[i] & 0x80)||(data[i] < 32) ? '.' : data[i]);
	fprintf(fp, "\n");
}

void binDump(FILE *fp, void *d, unsigned int length)
{
	unsigned char *data = (unsigned char *)d;
	int offset=0;
	fprintf(fp, "Binary Dump at [0x%08x][%u]\n",(int)data, length);
	while(length>16)
	{
		fprintf(fp, "%08x : ",offset);
		binLineDump(fp, data, 16);
		data+=16;
		offset+=16;
		length-=16;
	}
	fprintf(fp, "%08x : ",offset);
	binLineDump(fp, data, length);
}

#ifdef FILE_TEST_MODE
static int discard_unconvertible = 0;

static int convert (codeconv_t cd, FILE* infile, const char* infilename)
{
	char inbuf[4096+4096];
	size_t inbufrest = 0;
	char outbuf[4096];
	int status = 0;

#if O_BINARY
	if (force_binary) SET_BINARY(fileno(infile));
#endif
	codeconv(cd,NULL,NULL,NULL,NULL);
	for (;;)
	{
		size_t inbufsize = fread(inbuf+4096,1,4096,infile);
		if (inbufsize == 0)
		{
			if (inbufrest == 0)
				break;
			else
			{
				fprintf(stderr, "codeconv: %s: incomplete character or shift sequence\n", infilename);
				return 1;
			}
		}
		else
		{
			char* inptr = inbuf+4096-inbufrest;
			size_t insize = inbufrest+inbufsize;
			inbufrest = 0;
			binDump(stdout, inbuf+4096, inbufsize);
			while (insize > 0)
			{
				char* outptr = outbuf;
				size_t outsize = sizeof(outbuf);
				size_t res = 0;
				printf("inptr = %p, insize = %d, outptr = %p, outsize = %d\n",
						inptr, insize, outptr, outsize);
				res = codeconv(cd, &inptr, &insize, &outptr, &outsize);
				printf("inptr = %p, insize = %d, outptr = %p, outsize = %d\n",
						inptr, insize, outptr, outsize);
				if (outptr != outbuf)
				{
					int saved_errno = errno;
					if (fwrite(outbuf,1,outptr-outbuf,stdout) < outptr-outbuf)
						return 1;
					errno = saved_errno;
				}
				if (res == (size_t)(-1))
				{
					if (errno == EILSEQ)
					{
						if (discard_unconvertible == 1)
						{
							int one = 1;
							iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, &one);
							discard_unconvertible = 2;
							status = 1;
						}
						else
						{
							fprintf(stderr,"codeconv(1): %s: cannot convert\n",infilename);
							return 1;
						}
					}
					else if (errno == EINVAL)
					{
						if (inbufsize == 0 || insize > 4096)
						{
							fprintf(stderr,"codeconv: %s: incomplete character or shift sequence\n",infilename);
							return 1;
						}
						else
						{
							inbufrest = insize;
							if (insize > 0)
							{
								/* Like memcpy(inbuf+4096-insize,inptr,insize), except that
								we cannot use memcpy here, because source and destination
								regions may overlap. */
								char* restptr = inbuf+4096-insize;
								do { *restptr++ = *inptr++; } while (--insize > 0);
							}
							break;
						}
					}
					else if (errno != E2BIG)
					{
						int saved_errno = errno;
						fprintf(stderr,"codeconv: %s: ",infilename);
						errno = saved_errno;
						perror("");
						return 1;
					}
				}
			}
		}
	}

	{
		char* outptr = outbuf;
		size_t outsize = sizeof(outbuf);
		size_t res = codeconv(cd, NULL, NULL, &outptr, &outsize);
		if (outptr != outbuf)
		{
			int saved_errno = errno;
			if (fwrite(outbuf,1,outptr-outbuf,stdout) < outptr-outbuf)
				return 1;
			errno = saved_errno;
		}
		if (res == (size_t)(-1))
		{
			if (errno == EILSEQ)
			{
				if (discard_unconvertible == 1)
				{
					int one = 1;
					iconvctl(cd, ICONV_SET_DISCARD_ILSEQ, &one);
					discard_unconvertible = 2;
					status = 1;
				}
				else
				{
					fprintf(stderr,"codeconv(2): %s: cannot convert\n",infilename);
					return 1;
				}
			}
			else if (errno == EINVAL)
			{
				fprintf(stderr,"codeconv: %s: incomplete character or shift sequence\n",infilename);
				return 1;
			}
			else
			{
				int saved_errno = errno;
				fprintf(stderr,"codeconv: %s: ",infilename);
				errno = saved_errno;
				perror("");
				return 1;
			}
		}
	}

	if (ferror(infile))
	{
		fprintf(stderr,"codeconv: %s: I/O error\n",infilename);
		return 1;
	}
	return status;
}
#endif

static int _dumpList(unsigned int namescount, const char * const * names, void* data)
{
	unsigned int i;
	for (i = 0; i < namescount; i++)
		printf("%s\n", names[i]);
	return 0;
}

int main(void)
{
	codeconv_t cd = (codeconv_t)-1;
	codeconv_list(_dumpList, NULL);

	if ((cd = codeconv_open("UTF-8", "EUC-KR")) == (codeconv_t)(-1))
		printf("codeconv_open = %s(%d)\n", strerror(errno), errno);
	else
	{
#ifndef FILE_TEST_MODE
		char ibuf[1024] = "°¡³ª\0", *in_buf = ibuf;
		char obuf[1024], *out_buf = obuf;
		char *bp = obuf;
		size_t in_size = strlen(in_buf);
		size_t out_size = 1024;
		size_t ret_size = 0;

		fprintf(stdout, "inbuf[EUC-KR] ------------\n");
		binDump(stdout, ibuf, in_size);

		codeconv(cd, NULL, NULL, NULL, NULL);

		fprintf(stdout, "convert ----------\n");
		while(in_size > 0)
		{
			if (codeconv(cd, &in_buf, &in_size, &out_buf, &out_size) < 0)
			{
				printf("codeconv = %s(%d)\n", strerror(errno), errno);
				break;
			}
			else
			{
				ret_size += (out_buf - bp);
				fwrite(obuf, 1, out_buf - bp, stdout);
				bp = out_buf;
			}
		}
		printf("\n");
		codeconv_close(cd);

		fprintf(stdout, "outbuf[UTF-8] ------------\n");
		binDump(stdout, obuf, ret_size);

		cd = codeconv_open("EUCKR", "UTF-8");
		if (cd == (codeconv_t)(-1))
			printf("codeconv_open = %s(%d)\n", strerror(errno), errno);
		else
		{
			in_size = ret_size;
			memcpy(ibuf, obuf, in_size);
			in_buf = ibuf;

			out_buf = obuf;
			out_size = 1024;

			codeconv(cd, NULL, NULL, NULL, NULL);

			ret_size = 0; bp = obuf;

			fprintf(stdout, "convert ----------\n");
			while(in_size > 0)
			{
				if (codeconv(cd, &in_buf, &in_size, &out_buf, &out_size) < 0)
				{
					printf("codeconv = %s(%d)\n", strerror(errno), errno);
					break;
				}
				else
				{
					ret_size += (out_buf - bp);
					fwrite(obuf, 1, out_buf - bp, stdout);
					bp = out_buf;
				}
			}
			printf("\n");
			codeconv_close(cd);

			fprintf(stdout, "outbuf[EUC-KR] -----------\n");
			binDump(stdout, obuf, ret_size);
		}
#else
		FILE *fp = fopen("test.txt", "rb");
		if (fp)
		{
			convert(cd, fp, "test.txt");
			fclose(fp);
		}
		else
			printf("fopen = %s(%d)\n", strerror(errno), errno);
#endif
	}
	return 0;
}

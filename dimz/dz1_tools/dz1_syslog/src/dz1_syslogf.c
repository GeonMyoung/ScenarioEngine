#include <dz1_malloc.h>
#include "dz1_syslog.h"

typedef struct Dz1SyslogFile
{
	pthread_mutex_t		 lock;
	FILE				*fp;
	TCHAR				 path[1024];
	TCHAR				 basename[256];
	size_t				 seg_size;
//	u32_t				 seg_cnt;
} Dz1SyslogFile;


//////////////////////////////////////////////////////////////////////////////////////////////
// Critical
static bool_t _mgmt_out(Dz1Str path, Dz1Str basename, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	struct tm tmC;
	if (Dz1File_getTime3(NULL, &tmC, NULL, path, basename, Dz1Text("log.txt"), errp) == FALSE) ERR_OUT(errp);
	else
	{
		TCHAR dst_name_ext[64];
		snprintf(dst_name_ext, 64, Dz1Text("%s.%04d%02d%02d.%02d%02d%02d"), basename, tmC.tm_year + 1900, tmC.tm_mon + 1, tmC.tm_mday, tmC.tm_hour, tmC.tm_min, tmC.tm_sec);
		if ((*errp = Dz1File_rename3(path, dst_name_ext, Dz1Text("txt"), path, basename, Dz1Text("log.txt"))).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// static ssize_t Dz1SyslogFileName_appendPathStr(Dz1Str dst, size_t dst_sz, Dz1Str path_str, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ssize_t ret = -1;
// 	size_t len = 0;
// 	if (dst == NULL || Dz1Str_isVoid(path_str)) Dz1Error_set(errp,EINVAL);
// 	else if (dst_sz <= (len = Dz1STRLEN(path_str))) Dz1Error_set(errp, ENOMEM);
// 	else
// 	{
// 		TCHAR *dp = dst, *sp = path_str, *bp = NULL;
// 
// 		while(*dp) dp++;				// goto end
// 		if (dp > dst)
// 		{	// dst has letters
// 			dp--;
// 			if (*dp != DIR_SEP) dp++;	// suppress DIR_SEP
// 		}
// 
// 		bp = dp;						// save start point
// 
// 		if (*sp == DIR_SEP) sp++;		// suppress DIR_SEP
// 
// 		*dp++ = DIR_SEP;				// append DIR_SEP
// 		while(*sp) *dp++ = *sp++;		// copy path
// 		
// 		if (dp > bp)
// 		{
// 			dp--;
// 			if (*dp != DIR_SEP) dp++;	// trim DIR_SEP
// 		}
// 
// 		*dp = 0;
// 		ret = (ssize_t)(dp - dst);
// 	}
// 	return ret;
// }

// static ssize_t Dz1SyslogFileName_appendExtStr(Dz1Str dst, size_t dst_sz, Dz1Str ext_str, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	ssize_t ret = -1;
// 	size_t len = 0;
// 	if (dst == NULL || Dz1Str_isVoid(ext_str)) Dz1Error_set(errp,EINVAL);
// 	else if (dst_sz <= (len = Dz1STRLEN(ext_str))) Dz1Error_set(errp, ENOMEM);
// 	else
// 	{
// 		TCHAR *dp = dst, *sp = ext_str;
// 
// 		while(*dp) dp++;				// goto end
// 		*dp++ = Dz1Text('.');			// append DOT
// 		while(*sp) *dp++ = *sp++;		// copy string
// 		*dp = 0;
// 		ret = (ssize_t)(dp - dst);
// 	}
// 	return ret;
// }

// static bool_t Dz1SyslogFile_rename(Dz1Str path, Dz1Str dstName, Dz1Str dstExt, Dz1Str srcName, Dz1Str srcExt, Dz1Error *err)
// {
// 	DZ1_ERROR_SAFE_PTR(errp, err);
// 	TCHAR src[4096] = { 0 }, dst[4096] = { 0 };
// 	if (0) { }
// 	else if (Dz1Str_isVoid(path) == TRUE) Dz1Error_set(errp, EINVAL);
// 	else if (Dz1Str_isVoid(dstName) == TRUE && Dz1Str_isVoid(dstExt) == TRUE) Dz1Error_set(errp, EINVAL);
// 	else if (Dz1Str_isVoid(srcName) == TRUE && Dz1Str_isVoid(srcExt) == TRUE) Dz1Error_set(errp, EINVAL);
// 	else
// 	{
// 		TCHAR *dp = NULL;
// 		ssize_t sz = 0, size = 0;
// 
// 		dp = src; size = 4095;
// 		if ((sz = Dz1SyslogFileName_appendPathStr(dp, size, path, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 		if ((sz = Dz1SyslogFileName_appendPathStr(dp, size, srcName, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 		if ((sz = Dz1SyslogFileName_appendExtStr(dp, size, srcExt, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 
// 		dp = dst; size = 4095;
// 		if ((sz = Dz1SyslogFileName_appendPathStr(dp, size, path, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 		if ((sz = Dz1SyslogFileName_appendPathStr(dp, size, dstName, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 		if ((sz = Dz1SyslogFileName_appendExtStr(dp, size, dstExt, errp)) < 0) return FALSE; else { dp += sz; size -= sz; }
// 
// 		if ((*errp = Dz1File_rename(dst, src)).code) { }
// 		else Dz1Error_set(errp, 0);
// 	}
// 	return errp->code == 0 ? TRUE : FALSE;
// }

static bool_t Dz1SyslogFile_open(Dz1SyslogFile *slf, Dz1Error *err)
{	// slf가 기록 대상임으로 이 함수 내에서는 로그 기록을 남기면 안됨
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (slf->fp != NULL) 
	{	// close current stream 
		fclose(slf->fp); 
		slf->fp = NULL; 
	}

	// move out or delete current log file
	if (_mgmt_out(slf->path, slf->basename, NULL) == FALSE) 
		Dz1File_delete3(slf->path, slf->basename, Dz1Text("log.txt"));

	// open new log file
	if ((slf->fp = Dz1FileStream_open3(slf->path, slf->basename, Dz1Text("log.txt"), Dz1Text("wb"), errp)) == NULL) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return errp->code == 0 ? TRUE : FALSE;
}
// Critical
//////////////////////////////////////////////////////////////////////////////////////////////

#define SIZE_1_MEGA_BYTE			0x00100000
static bool_t Dz1SyslogFile_init(Dz1SyslogFile *p, Dz1Str path, Dz1Str basename, size_t seg_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL || Dz1Str_isVoid(basename) == TRUE || seg_size < SIZE_1_MEGA_BYTE) Dz1Error_set(errp, EINVAL);
	else
	{
		int code = 0;

		if (Dz1Str_isVoid(path) == FALSE) Dz1STRNCPY(p->path, path, 1023);
		Dz1STRNCPY(p->basename, basename, 255);
		p->seg_size = seg_size;

		if (Dz1Str_isVoid(path) == FALSE) Dz1Dir_mkDirNested(path);

		if ((code = pthread_mutex_init(&p->lock, NULL)) != 0) ERR_SET_OUT(errp, code);
		else if (Dz1SyslogFile_open(p, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

Dz1SyslogF *Dz1SyslogF_new(Dz1Str path, Dz1Str basename, size_t seg_size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1SyslogFile *ret = NULL;
	if ((ret = (Dz1SyslogFile *)Dz1Calloc(sizeof(Dz1SyslogFile), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1SyslogF_delAndSetNull, (void *)&ret);
		if (Dz1SyslogFile_init(ret, path, basename, seg_size, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1SyslogF_delAndSetNull, (void *)&ret);
	}
	return (Dz1SyslogF *)ret;
}

static void Dz1SyslogFile_clean(Dz1SyslogFile *p)
{
	if (p == NULL) { }
	else
	{
		pthread_mutex_lock(&p->lock);
		Dz1FileStream_closeAndSetNull(&p->fp);
		pthread_mutex_unlock(&p->lock);
	}
}

void Dz1SyslogF_del(Dz1SyslogF *ptr)
{
	Dz1SyslogFile *p = (Dz1SyslogFile *)ptr;
	if (p == NULL) return;
	else
	{
		Dz1SyslogFile_clean(p);
		pthread_mutex_destroy(&p->lock);
	}
}

bool_t Dz1SyslogF_write(Dz1SyslogF *p, u8_t *data, size_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	
	Dz1SyslogFile *slf = (Dz1SyslogFile *)p;
	if (slf != NULL && slf->fp != NULL)
	{
		long pos;
		pthread_mutex_lock(&slf->lock);
		pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&slf->lock);

		fwrite(data, sizeof(char), size, slf->fp);
		fflush(slf->fp);

		pos = ftell(slf->fp);
		if ((size_t)pos >= slf->seg_size) Dz1SyslogFile_open(slf, NULL);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

void Dz1SysLogF_hook(void *ptr, u8_t *data, size_t size) 
{ 
	Dz1SyslogF *slf = (Dz1SyslogF *)ptr;
	Dz1SyslogF_write(slf, data, size, NULL); 
}

void Dz1SysLogF_memExport(Dz1SyslogF *p, bool_t exportData)
{
	Dz1SyslogFile *slf = (Dz1SyslogFile *)p;
	pthread_mutex_lock(&slf->lock);
	if (slf->fp != NULL) Dz1Mem_export(slf->fp, exportData);
	pthread_mutex_unlock(&slf->lock);
}


static Dz1SyslogFile _default_syslog_ =
{
	PTHREAD_MUTEX_INITIALIZER,
	NULL,
	Dz1Text("."),
	Dz1Text("default"),
	0x2000000									// 32MB
};

Dz1Error Dz1SysLogFS_init(Dz1Str path, Dz1Str basename, size_t segSize)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SyslogFile *p = &_default_syslog_;
	if (Dz1SyslogFile_init(p, path, basename, segSize, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

void Dz1SysLogFS_clean(void)
{
	Dz1SyslogFile *p = &_default_syslog_;
	Dz1SyslogFile_clean(p);
}

Dz1Error Dz1SysLogFS_write(u8_t *data, size_t size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	Dz1SyslogFile *p = &_default_syslog_;
	if (Dz1SyslogF_write(p, data, size, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

void Dz1SysLogFS_hook(void *ptr, u8_t *data, size_t size)
{
	Dz1SyslogFile *p = &_default_syslog_;
	Dz1SyslogF_write(p, data, size, NULL); 
}

void Dz1SysLogFS_memExport(bool_t exportData)
{
	Dz1SyslogFile *p = &_default_syslog_;
	Dz1SysLogF_memExport(p, exportData);
}

#include <dz1_stdio.h>
#include <dz1_str.h>
#include <dz1_malloc.h>
#include <dz1_syslog.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static TCHAR path[4096] = { 0, };
static TCHAR names[4][4096] = { { 0, }, };
static size_t segSize = 0;

static FILE *syslog = NULL;

static Dz1Error _syslogOpen(void)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((syslog = Dz1FileStream_open2(path, names[0], Dz1Text("a+b"), errp)) == NULL)
	{
		if ((syslog = Dz1FileStream_open2(path, names[0], Dz1Text("wb"), errp)) == NULL) Dz1Error_set(errp, errno);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

static Dz1Error _shiftOut(void)
{
	size_t i;
	DZ1_ERROR_SAFE_VAR(errp, err);
	TCHAR fnOld[4096], fnNew[4096];

	if (syslog != NULL) Dz1FileStream_closeAndSetNull(&syslog);

	Dz1File_delete2(path, names[3]);
	for (i = 3; i > 0; i--)
	{
		if (0) { }
		else if (_Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, fnOld), path, names[i - 1], NULL) == FALSE) { }
		else if (_Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, fnNew), path, names[i], NULL) == FALSE) { }
		else Dz1File_rename(fnNew, fnOld);
	}

	if ((*errp = _syslogOpen()).code) { /*ERR_OUT(errp);*/ }
	else Dz1Error_set(errp, 0);

	return err;
}

static void _dataclean(void *p)
{
	size_t i;
	memset(path, 0, 4096 * sizeof(TCHAR));
	for (i = 0; i < 4; i++) memset(names[i], 0, 4096 * sizeof(TCHAR));
	segSize = 0;
}

static bool_t _isexist(Dz1Str name)
{
	size_t i;
	for (i = 0; i < 4; i++)
		if (Dz1STRCMP(names[i], name) == 0) return TRUE;
	return FALSE;
}

static Dz1Error _dataInit(Dz1Str _path, Dz1Str _basename, size_t _segSize)
{
	Dz1DirCatalog *cat = NULL;
	DZ1_ERROR_SAFE_VAR(errp, err);

	size_t i;

	Dz1STRCPY(path, _path);
	Dz1STRCPY(names[0], _basename);
	for (i = 1; i < 4; i++) Dz1SNPRINTF(names[i], 4095,Dz1Text("%s.%u"), _basename, (u32_t)i);
	segSize = _segSize;

	pthread_cleanup_push(_dataclean, NULL);

	Dz1Dir_mkDirNested(_path);

	if ((cat = Dz1DirCatalog_new(_path, errp)) == NULL) { /*ERR_OUT(errp);*/ }
	else
	{
		size_t i;
		Dz1DirEntry *p = NULL;

		pthread_cleanup_push((Dz1DelFunc)Dz1DirCatalog_del, (void *)cat);

		for (i = 0; i < cat->valid; i++)
		{
			p = &cat->entries[i];
			if (_isexist(p->name) == FALSE) Dz1File_delete2(cat->path, p->name);
		}

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1DirCatalog_del, (void *)cat);
	}
	pthread_cleanup_pop(errp->code); // (_dataclean, NULL);
	return err;
}


Dz1Error Dz1SysLog_init(Dz1Str _path, Dz1Str _basename, size_t _segSize)
{
	size_t pathSize, nameSize;
	DZ1_ERROR_SAFE_VAR(errp, err);
	
	pthread_mutex_lock(&lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);

	if (syslog != NULL) ERR_SET_OUT(errp, EEXIST);
	else if (!_path || (pathSize = Dz1STRLEN(_path)) == 0 || pathSize >= 4096) ERR_SET_OUT(errp, EINVAL);
	else if (!_basename || (nameSize = Dz1STRLEN(_basename)) == 0 || nameSize >= 4096) ERR_SET_OUT(errp, EINVAL);
	else if (_segSize == 0 || _segSize > 0x10000000) ERR_SET_OUT(errp, EINVAL);	// Maximum 256MB per log file
	else if ((*errp = _dataInit(_path, _basename, _segSize)).code) ERR_OUT(errp);
	else if ((*errp = _syslogOpen()).code) ERR_OUT(errp);

	pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
	return err;
}

static void _fseek_end(void *ptr)
{
	FILE *fp = (FILE *)ptr;
	fseek(fp, 0, SEEK_END);
}

static ssize_t _getFileSize(FILE *fp, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (fseek(fp, 0, SEEK_END) != 0) ERR_SET_OUT(errp, EFAULT);
	else if ((ret = ftell(fp)) == -1L) ERR_SET_OUT(errp, EFAULT);
	else if (fseek(fp, 0, SEEK_SET) != 0) { ERR_SET_OUT(errp, EFAULT); ret = -1; }
	return ret;
}

Dz1Binary *Dz1Syslog_get(Dz1Error *err)
{
	ssize_t firstLogSize = 0;
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	pthread_mutex_lock(&lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);

	// Check File Log.0
	if (syslog == NULL) Dz1Error_set(errp, ENOSYS);
	else if ((firstLogSize = ftell(syslog)) == -1L) Dz1Error_set(errp, EFAULT);
	else if (fseek(syslog, 0, SEEK_SET) != 0) Dz1Error_set(errp, EFAULT);			// rewind to first
	else
	{
		pthread_cleanup_push(_fseek_end, (void *)syslog);							// reserve forward to end
		if ((ret = Dz1Binary_new(NULL, 0, errp)) == NULL) { /*ERR_OUT(errp);*/ }
		else
		{
			TCHAR fn[4096];
			FILE *fp = NULL;

			pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);

			// Check File : log.1
			_Dz1FileName_concatPathName(Dz1ArrParam(TCHAR, fn), path, names[1], NULL);
			if ((fp = fopen(fn, "rb")) == NULL)	// log.1을 열 수가 없었다
			{	// 0
				if ((ret->data = (u8_t *)Dz1Malloc((ret->size = (u32_t)firstLogSize), errp)) == NULL) { /*ERR_OUT(errp);*/ }
				// Load Log File 0
				else if (fread(ret->data, sizeof(u8_t), ret->size, syslog) != ret->size) Dz1Error_set(errp, EFAULT);
				else Dz1Error_set(errp, 0);
			}
			else
			{	// 0 + 1
				ssize_t secondLogSize = 0;
				pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

				if ((secondLogSize = _getFileSize(fp, errp)) < 0) ERR_OUT(errp);
				else if ((ret->data = (u8_t *)Dz1Malloc((ret->size = (u32_t)(firstLogSize + secondLogSize)), errp)) == NULL) ERR_OUT(errp);
				else 
				{
					u8_t *cp = ret->data, *dp = ret->data + firstLogSize;
					if (fread(dp, sizeof(u8_t), secondLogSize, fp) != secondLogSize) ERR_SET_OUT(errp, EFAULT);
					else if (fread(cp, sizeof(u8_t), firstLogSize, syslog) != firstLogSize) ERR_SET_OUT(errp, EFAULT);
				}
				pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
		}
		pthread_cleanup_pop(1); // (_fseek_end, (void *)syslog);
	}
	pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
	return ret;
}

Dz1Error Dz1SysLog_write(u8_t *data, size_t size)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	
	pthread_mutex_lock(&lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);

	if (syslog != NULL)
	{
		long pos;
		fwrite(data, sizeof(char), size, syslog);
		fflush(syslog);
		pos = ftell(syslog);
		if ((size_t)pos >= segSize)
			_shiftOut();
	}

	pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
	return err;
}

void Dz1SysLog_hook(void *ptr, u8_t *data, size_t size) { Dz1SysLog_write(data, size); }

void Dz1SysLog_memExport(bool_t exportData)
{
	if (syslog) Dz1Mem_export(syslog, exportData);
}

void Dz1SysLog_clean(void)
{
	pthread_mutex_lock(&lock);
	pthread_cleanup_push((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);

	_dataclean(NULL);

	if (syslog) fclose(syslog);
	syslog = NULL;

	pthread_cleanup_pop(1); // ((Dz1DelFunc)pthread_mutex_unlock, (void *)&lock);
}

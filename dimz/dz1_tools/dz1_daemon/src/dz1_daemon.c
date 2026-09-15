#include <dz1_malloc.h>
#include "dz1_daemon.h"

typedef struct PathData
{
	TCHAR		 pwd_path[4096];
	TCHAR		 img_path[4096];
} PathData;

#define minimum_value(a, b)				((a < b) ? a : b)

bool_t Dz1Daemon_getMyPath(TCHAR *path, size_t path_len, TCHAR *name_ext, size_t name_ext_len, Dz1Str argv0, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	PathData *env = (PathData *)Dz1Calloc(sizeof(PathData), 1, errp);
	if (env == NULL) ERR_OUT(errp);
	else
	{
		ssize_t img_path_len = 0, pwd_path_len = 0;
		TCHAR *dp = env->img_path, *sp = argv0;
		TCHAR *cp = NULL, *np = NULL;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&env);

		if ((cp = Dz1STRRCHR(sp, DIR_SEP)) == NULL) np = sp; else np = cp + 1;
		
		// Copy Name
		if (name_ext != NULL && name_ext_len > 0) Dz1STRNCPY(name_ext, np, name_ext_len);

		// Make image location path
		while(sp < cp) { *dp++ = *sp++; img_path_len++; } *dp = 0;

		if ((pwd_path_len = Dz1Dir_pwd(env->pwd_path, 4096, errp)) < 0) ERR_OUT(errp);
		else if (Dz1STRNCMP(env->pwd_path, env->img_path, minimum_value(pwd_path_len, img_path_len)) == 0)	// 이미지 경로가 현재경로의 하위경로다
			Dz1STRNCPY(path, env->pwd_path, path_len);
		else Dz1STRNCPY(path, env->img_path, path_len);

		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&env);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

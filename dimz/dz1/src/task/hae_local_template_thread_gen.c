#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static char *srcBase= "\
#include <pthread.h>\n\
#include <sys/time.h>\n\
#include <hae_local_memory.h>\n\
#include <hae_local_thread.h>\n\
#include <hae_local_template_thread.h> \n\
#include <hae_local_sig_msg.h> \n\
#include <hae_tvfunc.h>\n\
#include \"$BASENAME$.h\"\n\
\n\
typedef struct $NAME$Arg\n\
{\n\
	// Define Member Variable\n\
} $NAME$Arg;\n\
\n\
static void $FUNCPREFIX$Arg_del($NAME$Arg *p)\n\
{\n\
	if (!p) return;\n\
\n\
	// $NAME$Arg Release Member Memory\n\
\n\
	LOCAL_FREE(p);\n\
}\n\
\n\
static void $FUNCPREFIX$Arg_delAndSetNull(void *ptr)\n\
{\n\
	$NAME$Arg **p = ($NAME$Arg **)ptr;\n\
	$FUNCPREFIX$Arg_del(*p); *p = NULL;\n\
}\n\
\n\
static $NAME$Arg *$FUNCPREFIX$Arg_new(int *err)\n\
{\n\
	int local_err, *errp = err ? err : &local_err;\n\
	$NAME$Arg *ret = ($NAME$Arg *)LOCAL_MALLOC(sizeof($NAME$Arg));\n\
	if (ret == NULL) { *errp = ENOMEM; }\n\
	{\n\
		memset(ret, 0, sizeof($NAME$Arg));\n\
		// $NAME$Arg Default Value Setting Code Here\n\
		pthread_cleanup_push($FUNCPREFIX$Arg_delAndSetNull, (void *)&ret);\n\
		\n\
		// $NAME$Arg Initialize Member Code Here\n\
		*errp = 0;\n\
		\n\
		pthread_cleanup_pop(*errp); // ($FUNCPREFIX$Arg_delAndSetNull, (void *)&ret);\n\
	}\n\
	return ret;\n\
}\n\
\n\
typedef struct $NAME$Env\n\
{\n\
	// Define Member Variable\n\
} $NAME$Env;\n\
\n\
static void $FUNCPREFIX$Env_del($NAME$Env *p)\n\
{\n\
	if (!p) return;\n\
\n\
	// $NAME$Env Release Member Memory\n\
\n\
	LOCAL_FREE(p);\n\
}\n\
\n\
static void $FUNCPREFIX$Env_delAndSetNull(void *ptr)\n\
{\n\
	$NAME$Env **p = ($NAME$Env **)ptr;\n\
	$FUNCPREFIX$Env_del(*p); *p = NULL;\n\
}\n\
\n\
static $NAME$Env *$FUNCPREFIX$Env_new(int *err)\n\
{\n\
	int local_err, *errp = err ? err : &local_err;\n\
	$NAME$Env *ret = ($NAME$Env *)LOCAL_MALLOC(sizeof($NAME$Env));\n\
	if (ret == NULL) { *errp = ENOMEM; }\n\
	{\n\
		memset(ret, 0, sizeof($NAME$Env));\n\
		// $NAME$Env Default Value Setting Code Here\n\
		pthread_cleanup_push($FUNCPREFIX$Env_delAndSetNull, (void *)&ret);\n\
		\n\
		// $NAME$Env Initialize Member Code Here\n\
		*errp = 0;\n\
		\n\
		pthread_cleanup_pop(*errp); // ($FUNCPREFIX$Env_delAndSetNull, (void *)&ret);\n\
	}\n\
	return ret;\n\
}\n\
\n\
static int $FUNCPREFIX$_getWaitTime(MessageProcessParam *p, struct timeval *to)\n\
{\n\
	int waitable = FALSE;\n\
	struct timeval tNow, tExpire;\n\
\n\
	// Decision Code Here what eather waitable or infinite\n\
	// waitable = \n\
\n\
	if (!waitable) return ESRCH;\n\
\n\
	gettimeofday(&tNow, NULL);\n\
\n\
	// Get Expire Time Stamp Code Here\n\
	// tExpire = \n\
\n\
	*to = hae_tvfunc_diff(tNow, tExpire);\n\
	return 0;\n\
}\n\
\n\
static int $FUNCPREFIX$_doTimeout(MessageProcessParam *p)\n\
{\n\
	// Timeout Processing Code Here \n\
\n\
	return 0; \n\
}\n\
\n\
static void $FUNCPREFIX$_clean(HaeLocalTemplateThreadParam *param, void *ptr)\n\
{\n\
	$NAME$Env *p = ($NAME$Env *)ptr;\n\
\n\
	if (!p) return;\n\
\n\
	// $NAME$Env Resource Destroy Code Here \n\
\n\
	$FUNCPREFIX$Env_del(p);\n\
}\n\
\n\
static void $FUNCPREFIX$_cleanAndSetNull(void *ptr)\n\
{\n\
	$NAME$Env **p = ($NAME$Env **)ptr;\n\
	$FUNCPREFIX$_clean(NULL, *p); *p = NULL;\n\
}\n\
\n\
static void *$FUNCPREFIX$_init(HaeLocalTemplateThreadParam *p, int *err)\n\
{\n\
	int local_err, *errp = err ? err : &local_err;\n\
	//$NAME$Arg *arg = ($NAME$Arg *)p->user_arg;\n\
	$NAME$Env *ret = NULL;\n\
\n\
	if ((ret = $FUNCPREFIX$Env_new(err)) == NULL) { *errp = ENOMEM; }\n\
	else\n\
	{\n\
		memset(ret, 0, sizeof($NAME$Env));\n\
		pthread_cleanup_push($FUNCPREFIX$_cleanAndSetNull, (void *)&ret);\n\
		\n\
		// $NAME$Env Member Initialize Code Here\n\
		\n\
		*errp = 0;\n\
		\n\
		pthread_cleanup_pop(*errp); // ($FUNCPREFIX$Env_delAndSetNull, (void *)&ret);\n\
	}\n\
\n\
	return ret;\n\
}\n\
\n\
static void $FUNCPREFIX$_exception(MessageProcessParam *p, int src_err)\n\
{\n\
	// Exception Handling Code Here\n\
}\n\
\n\
static HaeLocalTemplateThread *_$FUNCPREFIX$_new(u32_t peer_queue_id, $NAME$Arg *arg, int *arg_del, int *errp)\n\
{\n\
	HaeLocalTemplateThread *ret = NULL;\n\
	if ((ret = haeLocalTemplateThread_create(\"$NAME$\", peer_queue_id, $QUEUESIZE$,\n\
											arg, (HaeGeneralDelFunc)$FUNCPREFIX$Arg_del, arg_del,\n\
											$FUNCPREFIX$_init, $FUNCPREFIX$_clean,\n\
											$FUNCPREFIX$_exception,\n\
											$FUNCPREFIX$_getWaitTime, $FUNCPREFIX$_doTimeout, errp)) == NULL) { }\n\
	else\n\
	{\n\
		*arg_del = FALSE;\n\
		pthread_cleanup_push(HaeLocalTemplateThread_delAndSetNull, (void *)&ret);\n\
		\n\
		//if ((*errp = ret->reg(ret, __type__, __func__))) { }\n\
		//else if ((*errp = ret->reg(ret, __type__, __func__))) { }\n\
		//else\n\
		{ *errp = 0; }\n\
		\n\
		pthread_cleanup_pop(*errp); // (haeLocalTemplateThread_delAndSetNull, (void *)&ret);\n\
	}\n\
	return ret;\n\
}\n\
\n\
HaeLocalTemplateThread *$FUNCPREFIX$_new(u32_t peer_queue_id, int *err)\n\
{\n\
	int local_err, *errp = err ? err : &local_err;\n\
	HaeLocalTemplateThread *ret = NULL;\n\
	$NAME$Arg *arg = $FUNCPREFIX$Arg_new(errp);\n\
	if (arg == NULL) { }\n\
	else\n\
	{\n\
		int arg_del = TRUE;\n\
		pthread_cleanup_push((HaeGeneralDelFunc)$FUNCPREFIX$Arg_del, (void *)arg);\n\
		\n\
		if ((ret = _$FUNCPREFIX$_new(peer_queue_id, arg, &arg_del, errp)) == NULL) { }\n\
		\n\
		pthread_cleanup_pop(arg_del); // ((HaeGeneralDelFunc)$FUNCPREFIX$Arg_del, (void *)arg);\n\
	}\n\
	return ret;\n\
}\n\
\n\
void $FUNCPREFIX$_del(HaeLocalTemplateThread *p)\n\
{\n\
	if (!p) return;\n\
	haeLocalTemplateThread_del(p);\n\
}\n";

static char *hdrBase = "\
#ifndef $FILENAME$_H\n\
#define $FILENAME$_H\n\
\n\
#include <hae_local_template_thread.h>\n\
\n\
ASMLINK HaeLocalTemplateThread *$FUNCPREFIX$_new(u32_t peer_queue_id, int *err);\n\
ASMLINK void $FUNCPREFIX$_del(HaeLocalTemplateThread *p);\n\
\n\
#endif\n";

static char ucase(char c)
{
	if (c >= 'a' && c <= 'z') c = 'A' + (c - 'a');
	return c;
}

static char lcase(char c)
{
	if (c >= 'A' && c <= 'Z') c = 'a' + (c - 'A');
	return c;
}

static void usage(char *name)
{
	printf("HAE Local Template Thread Skel Code Generator 1.0\n");
	printf("%s <file_name> [<queue_size>]\n", name);
	printf("    queue_size is default to 64\n");
}

static int name_init(char *base, char name[128], char func_prefix[128], char file_name[128])
{
	int do_upper = 0;
	char *cp = base, *np = name, *fp = func_prefix, *filep = file_name;
	while(*cp)
	{
		if (isalpha((int)*cp) && !islower((int)*cp)) return EINVAL;
		if (*cp == '_') do_upper = 1;
		else
		{
			if (cp == base)
			{ // first bute
				*np++ = ucase(*cp);
				//*fp++ = lcase(*cp);
				*fp++ = ucase(*cp);
			}
			else
			{
				if (do_upper) { *np++ = *fp++ = ucase(*cp); do_upper = 0; }
				else *np++ = *fp++ = lcase(*cp);
			}
		}
		*filep++ = ucase(*cp);
		cp++;
	}
	*filep++ = *np = *fp = '\0';
	return 0;
}

static FILE *srcopen(char *fn)
{
	char buf[4096];
	sprintf(buf, "%s.c", fn);
	return fopen(buf, "wb");
}

static FILE *hdropen(char *fn)
{
	char buf[4096];
	sprintf(buf, "%s.h", fn);
	return fopen(buf, "wb");
}

static void publish(FILE *fp, char *cp, char *base_name, unsigned int queue_size)
{
	char name[128], func_prefix[128], file_name[128];

	name_init(base_name, name, func_prefix, file_name);

	while (*cp)
	{
		if (*cp != '$')
			fputc((int)*cp++, fp);
		else
		{
			char buf[128], *bp = buf;

			cp++;  while(*cp != '$') *bp++ = *cp++; cp++; *bp = '\0';// extract '$<TOKEN>$'

			if (strcmp(buf, "NAME") == 0) fprintf(fp, "%s", name);
			else if (strcmp(buf, "FUNCPREFIX") == 0) fprintf(fp, "%s", func_prefix);
			else if (strcmp(buf, "QUEUESIZE") == 0) fprintf(fp, "%u", queue_size);
			else if (strcmp(buf, "FILENAME") == 0) fprintf(fp, "%s", file_name);
			else if (strcmp(buf, "BASENAME") == 0) fprintf(fp, "%s", base_name);
			else
			{
				fprintf(stderr, "Unknown Token : %s\n", buf);
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	unsigned int queue_size = 64;
	if (argc == 3) queue_size = atoi(argv[2]);
	if (argc < 2 || argc > 3)
		usage(argv[0]);
	else
	{
		FILE *fp = NULL;
		char *cp = NULL;
		if ((fp = srcopen(argv[1]))) { cp = srcBase; publish(fp, cp, argv[1], queue_size); fclose(fp); }
		else fprintf(stderr, "Source File Open = %s(%d)\n", strerror(errno), errno);
		if ((fp = hdropen(argv[1]))) { cp = hdrBase; publish(fp, cp, argv[1], queue_size); fclose(fp); }
		else fprintf(stderr, "Header File Open = %s(%d)\n", strerror(errno), errno);
	}
	return 0;
}

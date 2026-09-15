#include <pthread.h>
#include <stdio.h>

int main(void)
{
	int fd = dup(fileno(stdout));
	FILE *fp = fdopen(fd, "wb");

	fprintf(fp, "test\n");
	fflush(fp);
	fclose(fp);
	printf("test1\n");
	printf("int = %d\n", sizeof(int));
	printf("long int = %d\n", sizeof(long int));
	printf("long long int = %d\n", sizeof(long long int));
	printf("pthread_mutex_t = %d\n", sizeof(pthread_mutex_t));
	printf("pthread_t = %d\n", sizeof(pthread_t));
	return 0;
}

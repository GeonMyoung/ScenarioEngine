#include <stdio.h>
#define test(exe)		{ int a = 10; exe; printf("%d\n", a); }

#define test1(arg)		do { printf arg; } while(0)

#define str(x)			#x
int main(void)
{
	test(int b = 20; a = 20; printf("%d\n", b));
	test1(("%d\n", 10));

	printf("%s\n", str(a));
	return 0;
}

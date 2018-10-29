#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void catch_SEGFAULT(int sig)
{
	printf("ERROR: the code contains a SEGFAULT error. Exiting ...\n");
	exit(1);
}

int main(void)
{
	signal(SIGSEGV, catch_SEGFAULT);

	int *p = 0;
	*p = 17;

	return 0;
}

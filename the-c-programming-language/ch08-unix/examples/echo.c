#include "syscalls.h"

int main(void)
{
	char buf[BUFSIZ];
	int n;

	while ((n = read(0, buf, BUFSIZ)) > 0)
		write(1, buf, BUFSIZ);
	return 0;
}

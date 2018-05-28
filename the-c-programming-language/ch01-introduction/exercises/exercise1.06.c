#include <stdio.h>

int main()
{
	/* will print 0 for CTRL-D, 1 for every other character */
	printf("getchar() != EOF is %d\n", getchar() != EOF);
	return 0;
}

#include <stdio.h>

/* copy input to output; 2nd version */
main()
{
	int c;

	printf("Enter lines of characters or CTRL-D to quit.\n");
	while ((c = getchar()) != EOF)
		putchar(c);
}

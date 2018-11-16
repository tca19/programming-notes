#include <stdio.h>

/* copy input to output; 1st version */
/* main()
 * {
 * 	int c = getchar();
 * 	while (c != EOF)
 * 	{
 * 		putchar(c);
 * 		c = getchar();
 * 	}
 * }
 */

/* copy input to output; 2nd version */
main()
{
	int c;

	printf("Enter lines of characters or CTRL-D to quit.\n");
	while ((c = getchar()) != EOF)
		putchar(c);
}

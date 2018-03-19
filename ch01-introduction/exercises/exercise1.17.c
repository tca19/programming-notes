#include <stdio.h>
#define MAXLENGTH 80

/* print all input lines that are longer than 80 characters */
int main()
{
	int c, length;
	char line[MAXLENGTH+1]; /* +1 to store '\0' */

	length = 0;
	while ((c = getchar()) != EOF)
	{
		/* line is longer than MAXLENGTH, print it and print all char
		 * until EOF or \n */
		if (length == MAXLENGTH)
		{
			line[length] = '\0';
			printf("%s", line);
			putchar(c);

			while (c != '\n' && (c = getchar()) != EOF)
				putchar(c);

			length = 0;
		}

		if (c == '\n')
			length = 0;
		else
			line[length++] = c;
	}

	return 0;
}

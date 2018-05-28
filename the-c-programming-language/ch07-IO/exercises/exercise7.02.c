#include <stdio.h>
#include <ctype.h>
#define TEXTWIDTH 80

/* print non printable character of input with hex representation, break long
 * lines */
int main(void)
{
	int c;
	int length;

	length = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == '\n')
		{
			printf("\n");
			length = 0;
		}
		else if (isspace(c) || isgraph(c))
			length += printf("%c",c);
		else
			length += printf(" 0x%d ", c);

		/* break long lines */
		if (length >= TEXTWIDTH)
		{
			printf("\n");
			length = 0;
		}
	}

	return 0;
}

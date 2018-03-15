#include <stdio.h>

/* copy input to output, replace consecutive blank characters by a single blank
 * character. */
int main()
{
	int c, was_blank;

	was_blank = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			if (!was_blank)
			{
				putchar(c);
				was_blank = 1;
			}
		}

		else
		{
			putchar(c);
			was_blank = 0;
		}
	}

	return 0;
}

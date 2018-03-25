#include <stdio.h>
#define MAXLINE 1000

/* rewrite the loop :
 *
 * for(i = 0; i<lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
 *     s[i] = c;
 *
 * without any && or ||.
 */
int main()
{
	int c, i, length;
	char line[MAXLINE];

	i = length = 0;
	while (i < MAXLINE-1)
	{
		c = getchar();
		if (c != '\n')
			if (c != EOF)
			{
				line[i++] = c;
				length = i;
			}
			else
				i = MAXLINE;
		else
			i = MAXLINE;
	}

	if (c == '\n')
		line[length++] = c;
	line[length] = '\0';

	printf("%d %s\n", length, line);
	return 0;
}

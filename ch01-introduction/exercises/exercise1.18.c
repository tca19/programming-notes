#include <stdio.h>
#define MAXLENGTH 1000

/* remove trailing blank and tabs from each line of input, delete entirely blank
 * lines */

int getline(char line[], int LIM)
{
	int c, l;

	for (l = 0; l < LIM-1 && ((c = getchar()) != EOF) && c != '\n'; ++l)
		line[l] = c;
	if (c == '\n')
		line[l++] = c;
	line[l] = '\0';

	return l;
}

int main()
{
	int length, last_non_blank;
	char line[MAXLENGTH];

	while ((length = getline(line, MAXLENGTH)) > 0)
	{
		/* line[length] is \0 */
		if (line[length-1] == '\n')
			last_non_blank = length-2;
		else
			last_non_blank = length-1;

		/* find position of last character that is not blank */
		while (last_non_blank > -1 && (line[last_non_blank] == '\t' ||
		                               line[last_non_blank] == ' '))
			--last_non_blank;

		/* if line is entirely blank, the position of last_non_blank
		 * would be -1, so we do not print the line */
		if (last_non_blank > -1)
		{
			line[last_non_blank+1] = '\0';
			printf("%s\n", line);
		}
	}

	return 0;
}

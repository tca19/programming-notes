#include <stdio.h>

/* count blanks, tabs and newline */
int main()
{
	int c, n_blank, n_tab, n_newline;

	n_blank = 0;
	n_tab = 0;
	n_newline = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
			++n_blank;
		if (c == '\t')
			++n_tab;
		if (c == '\n')
			++n_newline;
	}

	printf("blank: %d, tab: %d, newline: %d\n", n_blank, n_tab, n_newline);
	return 0;
}

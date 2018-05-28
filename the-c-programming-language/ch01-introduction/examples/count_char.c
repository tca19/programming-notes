#include <stdio.h>

/* count characters in input; 1st version */
main()
{
	long nc;

	nc = 0;
	printf("Enter some text then hit CTRL-D to exit and know the number of "
	       "characters in your text.\n");
	while (getchar() != EOF)
		++nc;
	printf("There are %ld characters in input.\n", nc);
}

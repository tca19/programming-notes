#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* convert input to lowercase or uppercase depending on name of program */
int main(int argc, char *argv[])
{
	int c;

	if (strcmp(argv[0], "./lower") == 0)
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (strcmp(argv[0], "./upper") == 0)
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	else
		printf("error: name of program is not ./lower or ./upper\n");

	return 0;
}

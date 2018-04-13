#include <stdio.h>

void strcat_(char *s, char *t)
{
	/* move s until '\0' */
	while (*s++)
		;
	s--; /* move back 1 char to overwrite '\0' when concatenating t */

	while ((*s++ = *t++))
		;
}

int main()
{
	char s1[MAXLEN] = "hello ";
	char s2[MAXLEN] = "world";

	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	strcat_(s1, s2);
	printf("s1+s2: %s\n", s1);

	return 0;
}

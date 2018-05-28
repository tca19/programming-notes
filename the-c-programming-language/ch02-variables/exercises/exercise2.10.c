#include <stdio.h>

/* lower: convert c to lower case (conditional operator instead of if-else) */
char lower(char c)
{
	return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
}

int main()
{
	char l = 'G';
	char m = 'z';
	char d = '8';
	printf("normal: %c, lowercase: %c\n", l, lower(l));
	printf("normal: %c, lowercase: %c\n", m, lower(m));
	printf("normal: %c, lowercase: %c\n", d, lower(d));
	return 0;
}

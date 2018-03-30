#include <limits.h>     /* INT_MIN */
#include <stdio.h>
#include <string.h>     /* strlen() */
#include <stdlib.h>     /* abs() */


void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; ++i, --j)
		c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n, char s[])
{
	int i, sign;

	sign = n; /* copy because we need to modify n */
	i = 0;

	do
	{
		s[i++] = abs(n%10) + '0';
	} while (n /= 10);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

int main()
{
	int x = INT_MIN;
	char s[100];

	itoa(x, s);
	printf("x: %d\nstr(x): %s\n", x, s);

	return 0;
}


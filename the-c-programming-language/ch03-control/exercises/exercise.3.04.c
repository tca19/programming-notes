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

/* In a two's complement number representation, numbers go from -2^(wordsize-1)
 * to 2^(wordsize-1)-1. For wordize = 32, we hence have -(-2^31) = -2^31 (the
 * same number). In that case, the variable n would still be negative after n =
 * -n. So the do...while loop would stop after 1 iteration because n / 10 would
 *  be negative (not correct because obviously we need more that 1 character to
 *  represent -2^31). We can replace the condition by : "do ... while n is not
 *  0".
 *
 * Moreover, for -2^31, the value (n%10) would also be negative and (n%10) + '0'
 * might not be a valid digit. So we need to take the absolute value of (n%10)
 * to handle that special case. This won't have any influence for all the other
 * number (in their case, n is positive).
 */

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


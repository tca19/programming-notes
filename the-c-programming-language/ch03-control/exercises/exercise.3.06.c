#include <stdio.h>

int itoa(int n, char s[], int width);
void reverse(char s[]);

/* itoa: convert n to string, pad left with blanks if length < width */
int itoa(int n, char s[], int width)
{
	int sign, i, d;

	sign = n;
	i = 0;
	do
	{
		d = (sign > 0) ? (n%10) : -(n%10);
		s[i++] = d + '0';
	} while (n /= 10);

	if (sign < 0)
		s[i++] = '-';

	while (i < width)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);

	return i;
}

/* reverse: reverse in place the string s */
void reverse(char s[])
{
	int len, c, i, j;

	len = 0;
	while (s[len] != '\0')
		++len;

	for (i = 0, j = len-1; i < j; ++i, --j)
		c = s[i], s[i] = s[j], s[j] = c;
}

int main()
{
	int n, w;
	char s[100];

	n = -2147483648;
	w = 15;
	itoa(n, s, w);
	printf("n: %d\nwidth: %d\nstr(n): %s\n", n, w, s);

	return 0;
}

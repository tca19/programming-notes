#include <stdio.h>

/* reverse: reverse in place the string s */
void reverse(char s[])
{
	int len, i, j, temp;

	len = 0;
	while (s[len] != '\0')
		++len;

	for (i = 0, j = len-1; i < j; ++i, --j)
		temp = s[i], s[i] = s[j], s[j] = temp;
}

/* itob: converts n into the base `base` character representation */
int itob(int n, char s[], int base)
{
	int sign, i, d;

	if (base < 2 || base > 36)
	{
		printf("ERROR: base must be between 2 <= base <= 36.\n");
		s[0] = '\0';
		return 0;
	}

	sign = n;
	i = 0;
	do
	{
		d = (sign > 0) ? n%base : -(n%base);
		if (d <= 9)
			s[i++] = d + '0';
		else
			s[i++] = (d-10) + 'a';
	} while (n /= base);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);

	return i;
}

int main()
{
	int x, base;
	char s[100];

	x = -2147483648;
	base = 36;

	itob(x, s, base);
	printf("x: %d\nx in base %d: %s\n", x, base, s);

	return 0;
}

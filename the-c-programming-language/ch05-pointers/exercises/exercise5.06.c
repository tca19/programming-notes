#include <stdio.h>
#define MAXLEN 100

/* atoi: convert s to integer; pointer version */
int atoi(char *s)
{
	int n;
	for (n = 0; *s >= '0' && *s <= '9'; s++)
		n = 10 * n + (*s - '0');
	return n;
}

/* reverse: reverse string s in place; pointer version */
void reverse(char *s)
{
	char temp, *t = s;

	while (*t) /* move t to the end of s */
		t++;
	t--;       /* leave \0 at its place */
	while (s < t)
	{
		temp = *s;
		*s++ = *t;
		*t-- = temp;
	}
}

/* itoa: convert n to its string representation; pointer version */
void itoa(int n, char *s)
{
	char *p = s;

	if (n < 0)
	{
		*p++ = '-';
		s++;      /* so - is not reversed */
		n = -n;
	}

	while (n > 0)
	{
		*p++ = n%10 + '0';
		n /= 10;
	}

	*p = '\0';
	reverse(s);
}

int main()
{
	char number[] = "123456789";
	char s[MAXLEN];
	int x, y = -879462;

	printf("--- atoi ---\n");
	printf("n: %s\n", number);
	x = atoi(number);
	printf("value read: %d\n\n", x);

	printf("--- itoa ---\n");
	printf("y: %d\n", y);
	itoa(y, s);
	printf("str(y): %s\n\n", s);

	printf("--- reverse ---\n");
	printf("before: %s\n", number);
	reverse(number);
	printf("after: %s\n", number);

	return 0;
}


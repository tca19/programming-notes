#include <stdio.h>

/* strend: return 1 if t occurs at the end of s, 0 otherwise */
int strend(char *s, char *t)
{
	char *rev_t = t, *rev_s = s;

	/* move rev_t to the end of t */
	while (*rev_t++);

	/* move rev_s to the end of s */
	while (*rev_s++);

	rev_t--;
	rev_s--;
	while ((*rev_t == *rev_s) && rev_t != t && rev_s != s)
	{
		rev_t--;
		rev_s--;
	}

	return rev_t == t;
}

int main()
{
	char s1[] = "hello";
	char s2[] = "lo";
	printf("\"%s\" at the end of \"%s\" ? %d\n", s2, s1, strend(s1, s2));

	return 0;
}

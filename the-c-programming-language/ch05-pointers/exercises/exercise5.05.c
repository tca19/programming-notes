#include<stdio.h>
#define MAXLEN 100

/* strncpy_: copies at most n characters of t to s */
void strncpy_(char *s, char *t, int n)
{
	int i = 0;

	while ( i < n && (*s++ = *t++))
		++i;
	*s = '\0';
}

/* strncat_: concatenate at most n characters of t to s */
void strncat_(char *s, char *t, int n)
{
	int i;

	while (*s++) /* move to the end of s */
		;
	s--;         /* overwrite '\0' */

	for (i = 0; i < n && (*s++ = *t++); ++i)
		;
	*s = '\0';
}

/* strncmp_: compare n char of s and t; return -1 if s<t, 1 if s>t, 0 if s=t */
int strncmp_(char *s, char *t, int n)
{
	int i;
	for (i = 0; i < n && *s != '\0' && *s == *t; ++i)
	{
		s++;
		t++;
	}

	if (i == n)
		return 0;

	if (*s == '\0')
	{
		if (*t == '\0')
			return 0;
		else      /* s is shorter than t, so s<t */
			return -1;
	}

	if (t == '\0') /* s is not \0, would have been caughtch with prev if */
		return 1;

	if (*s != *t)
		return (unsigned char) *s - (unsigned char) *t;

	return 0;
}

int main()
{
	char s1[MAXLEN] = "OK";
	char s2[MAXLEN] = "working";
	char s3[MAXLEN] = "computer";

	printf("--- strncpy_ ---\n");
	printf("s1: %s\ns2: %s\n", s1, s2);
	strncpy_(s1, s2, 4);
	printf("strncpy_(s1, s2, 4): %s\n\n", s1);

	printf("--- strncat_ ---\n");
	printf("s2: %s\ns3: %s\n", s2, s3);
	strncat_(s2, s3, 2);
	printf("strncat_(s2, s3, 2): %s\n\n", s2);

	printf("--- strncmp_ ---\n");
	printf("s1: %s\ns2: %s\n", s1, s2);
	printf("strncmp_(s1, s2, 8): %d\n", strncmp_(s1, s2, 8));
	printf("strncmp_(s1, s2, 4): %d\n", strncmp_(s1, s2, 4));

	return 0;
}

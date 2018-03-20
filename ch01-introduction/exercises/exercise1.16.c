#include <stdio.h>
#define MAXLINE 80  /* maximum input line size */

/* revised version of longest_line.c, print the length of arbitrarily long
 * input lines, and as much as possible of the text */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main()
{
	int len;                /* current line length */
	int max;                /* maximum length seen so far */
	char line[MAXLINE];     /* current input line */
	char longest[MAXLINE];  /* longest line saved here */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}

	if (max > 0)  /* there was a line */
		printf("Length: %d", max);
		if (max > MAXLINE)
			printf(" (overflow of %d characters)", max-MAXLINE);
		printf("\nLine: %s", longest);

	return 0;
}

/* getline: read a line into s, return length. If line is longer than LIM,
 * the end of line is cropped */
int getline(char s[], int LIM)
{
	int c, l;

	l = 0;
	while ((c = getchar()) != EOF && c != '\n' && l < LIM-1)
		s[l++] = c;

	/* we stopped reading line because line is too long. Need to find the
	 * length of whole line */
	if (l == LIM-1)
	{
		s[l] = '\0';
		++l; /* c was valid (not EOF or \n) but could not be added */
		while ((c = getchar()) != EOF && c != '\n')
			++l;
		if (c == '\n') ++l;
	}
	else if (c == '\n') /* stopped because end of line */
	{
		s[l++] = c;
		s[l] = '\0';
	}
	else /* stopped because EOF */
		s[l] = '\0';

	return l;
}

/* copy: copy `from` into `to`; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

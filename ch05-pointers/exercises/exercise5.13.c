#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES  5000      /* max #lines to read */
#define MAXLEN    1000
#define ALLOCSIZE 10000     /* size of available space */

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], char *buffer, int maxlines);
void writelines(char *lineptr[], int nlines, int n);
int getline(char *, int);

/* print last n lines (default 10) */
int main(int argc, char *argv[])
{
	int nlines, n;
	char lines_buffer[ALLOCSIZE];

	n = 10;
	if (argc > 1 &&  (*++argv)[0] == '-')
		n = -atoi(*argv);

	if ((nlines = readlines(lineptr, lines_buffer, MAXLINES)) >= 0)
		writelines(lineptr, nlines, n);
	else
	{
		printf("error: input too big to read\n");
		return -1;
	}

	return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], char *buffer, int maxlines)
{
	int len, next_free_pos, nlines;

	nlines = 0;
	next_free_pos = 0;
	while ((len = getline(&buffer[next_free_pos], MAXLEN)) > 0)
		if (nlines >= maxlines || next_free_pos + len > ALLOCSIZE)
			return -1;
		else
		{
			buffer[next_free_pos+len-1] = '\0';
			lineptr[nlines++] = buffer+next_free_pos;
			next_free_pos += len;
		}
	return nlines;
}

/* writelines: write to output last n lines; pointer version */
void writelines(char *lineptr[], int nlines, int n)
{
	if (n > nlines)
		n = nlines;
	lineptr += (nlines - n); /* advance to last n lines */
	nlines = n;              /* only (last) n lines to print */
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
	int c, i;

	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

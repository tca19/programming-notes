#include <stdio.h>
#include <string.h>

#define MAXLINES  5000      /* max #lines to be sorted */
#define MAXLEN    1000
#define ALLOCSIZE 10000     /* size of available space */

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], char *buffer, int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int getline(char *, int);

/* sort input lines */
int main()
{
	int nlines;
	char lines_buffer[ALLOCSIZE];

	if ((nlines = readlines(lineptr, lines_buffer, MAXLINES)) >= 0)
	{
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
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

/* writelines: write output lines; pointer version */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)    /* do nothing if arrays has fewer than 2 elems */
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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

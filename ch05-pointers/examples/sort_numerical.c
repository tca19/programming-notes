#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void sort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmp_p(char *, char *);

/* sort input lines */
int main(int argc, char *argv[])
{
	int nlines;                 /* number of input lines read */
	int numeric = 0;            /* 1 is numeric sort */

	if (argc > 1 && strcmp_p(argv[1], "-n") == 0)
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		sort((void **) lineptr, 0, nlines-1,
		  (int (*)(void*, void*))(numeric ? numcmp : strcmp_p));
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000     /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else
		{
			line[len-1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

/* sort: sort v[left]...v[right] into increasing order */
void sort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)    /* nothing to do if less than 2 elements */
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; ++i)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	sort(v, left, last-1, comp);
	sort(v, last+1, right, comp);
}

/* strcmp_p: return <0 if s<t, 0 if s==t, >0 if s>t: pointer version */
int strcmp_p(char *s, char *t)
{
	while (*s++ == *t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* swap: exchange p1 with p2 */
void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

char *alloc(int n)  /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) /* if fits */
	{
		allocp += n;
		return allocp - n; /* old position */
	}
	else                   /* not enough space */
		return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
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

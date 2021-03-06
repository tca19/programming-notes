#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 100

struct key
{
	char *word;
	int count;
} keytab[] = {
	{"auto",     0},
	{"break",    0},
	{"case",     0},
	{"char",     0},
	{"const",    0},
	{"continue", 0},
	{"default",  0},
	{"do",       0},
	{"double",   0},
	{"else",     0},
	{"enum",     0},
	{"extern",   0},
	{"float",    0},
	{"for",      0},
	{"goto",     0},
	{"if",       0},
	{"inline",   0},
	{"int",      0},
	{"long",     0},
	{"register", 0},
	{"restrict", 0},
	{"return",   0},
	{"short",    0},
	{"signed",   0},
	{"sizeof",   0},
	{"static",   0},
	{"struct",   0},
	{"switch",   0},
	{"typedef",  0},
	{"union",    0},
	{"unsigned", 0},
	{"void",     0},
	{"volatile", 0},
	{"while",    0}
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
#define NKEYS (sizeof keytab) / (sizeof(keytab[0]))

/* count C keywords; handle words with underscores, comments, preprocessor
 * control lines. */
int main(void)
{
	int n;
	char word[MAXLEN];

	while (getword(word, MAXLEN) != EOF)
	{
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	}
	for (n = 0; n < NKEYS; ++n)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]...tab|n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, mid, high;

	low = 0;
	high = n-1;
	while (low <= high)
	{
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid-1;
		else if (cond > 0)
			low = mid+1;
		else
			return mid;
	}
	return -1;
}

/* getword: get next word from input */
int getword(char *word, int lim)
{
	int c, next_c, getch(void);
	void ungetch(int);
	char *w = word;

	int inside_comment, inside_string;
	inside_comment = inside_string = 0;

	while (isspace(c = getch())) ;
	if (c != EOF)
		*w++ = c;

	/* look for potential comment */
	if (c == '/')
	{
		if ((next_c = getch()) == '*')
			inside_comment = 1;
		ungetch(next_c);
	}

	/* look for potential string constant */
	else if (c == '"')
		inside_string = 1;

	/* if word does not start with a valid char, consider this char to be a
	 * single word */
	else if (c != '_' && c != '#' && !isalpha(c))
	{
		*w = '\0';
		return c;
	}

	/* read characters, add them to word */
	for (; --lim > 0; w++)
	{
		*w = getch();

		/* potential end of comment, need to read next char to see if
		 * that's the case */
		if (inside_comment && *w == '*')
		{
			if ((next_c = getch()) == '/')
			{
				w++;
				*w++ = next_c;
				break;
			}
			ungetch(next_c);
		}

		/* end of string; w++ to not overwrite '"' when adding \0 */
		if (inside_string && *w == '"')
		{
			w++;
			break;
		}

		/* end of word = anything not alphanum or _ , only when not in
		 * comment of string (because every char is acceptable when in
		 * comment or string) */
		if (!inside_comment && !inside_string &&
		    !isalnum(*w) && *w != '_')
		{
			ungetch(*w);
			break;
		}
	}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];     /* buffer for ungetch */
int bufp = 0;          /* next free position in buf */

int getch(void) /* get a (possibly pushed back character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

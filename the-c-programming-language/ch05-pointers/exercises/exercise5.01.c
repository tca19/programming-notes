#include <stdio.h>
#include <ctype.h>

int getint(int *pn);
int getch(void);
void ungetch(int);

/* read an integer from stdin, - and + are considered errors if not followed by
 * any digit */
int main()
{
	int status, n;
	status = getint(&n);

	if (status == 0)
		printf("error: not a number\n");
	else if (status > 0)
		printf("value read: %d\n", n);

	return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, next, sign;

	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+')
	{
		next = getch();
		if (!isdigit(next))
		{
			ungetch(next);
			ungetch(c);
			return 0;
		}
		c = next;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
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

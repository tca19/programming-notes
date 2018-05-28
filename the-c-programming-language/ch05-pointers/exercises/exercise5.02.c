#include <stdio.h>
#include <ctype.h>

int getfloat(double *pf);
int getch(void);
void ungetch(int);

/* read a float from stdin, - and + are considered errors if not followed by
 * any digits */
int main()
{
	int status;
	double x;
	status = getfloat(&x);

	if (status == 0)
		printf("error: not a number\n");
	else if (status > 0)
		printf("value read: %f\n", x);

	return 0;
}

/* getfloat: get next float from input into *pf. Return an int (status code) */
int getfloat(double *pf)
{
	int c;
	double sign, pow = 1.0;

	/* skip white spaces */
	while ((c = getch()) == ' ' || c == '\t')
		;

	if (!isdigit(c) && c != EOF && c != '-' && c != '+')
	{
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1.0 : 1.0;
	if (c == '-' || c == '+')
		c = getch();
	for (*pf = 0.0; isdigit(c); c = getch())
		*pf = 10.0 * *pf + (c - '0');

	if (c == '.')
	{
		for (c = getch(); isdigit(c); c = getch())
		{
			*pf = 10.0 * *pf + (c - '0');
			pow *= 10.0;
		}
	}

	*pf = *pf * sign / pow;
	if (c == EOF)
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

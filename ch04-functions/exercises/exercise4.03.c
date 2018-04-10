#include <stdio.h>
#include <stdlib.h>    /* for atof() */
#include <ctype.h>     /* for isdigit() */
#include <math.h>

#define MAXOP   100    /* max size of operand or operator */
#define NUMBER  '0'    /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse polish calculator: add the % operator and negative numbers */
int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: modulo by zero\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL  100    /* maximum depth of val stack */

int sp = 0;            /* next free stack position */
double val[MAXVAL];    /* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top values from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	/* skip white spaces */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')
		return c;   /* not a number */

	i = 0;
	if (c == '-')
	{
		/* if next char is not a digit, then it was not a (possible)
		 * negative number. Return the '-' symbol and use ungetch() to
		 * make it look like nothing happened. */
		if (!isdigit(c = getch()))
		{
			ungetch(c);
			return '-';
		}
		s[++i] = c;
	}

	if (isdigit(c))     /* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')       /* collect decimal part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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

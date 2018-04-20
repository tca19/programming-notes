#include <stdio.h>
#include <ctype.h>
#include <string.h>

void push(double);
double pop(void);
int getfloat(char*, double*);

/* evaluate a reverse polish expression from the command line */
int main(int argc, char *argv[])
{
	double op2;

	if (argc < 2)
	{
		printf("error: at least 1 argument is required for eval.\n");
		return -1;
	}

	while (--argc > 0)
	{
		++argv;

		if (strcmp(*argv, "+") == 0)
			push(pop() + pop());

		else if (strcmp(*argv, "*") == 0)
			push(pop() * pop());

		else if (strcmp(*argv, "-") == 0)
		{
			op2 = pop();
			push(pop() - op2);
		}

		else if (strcmp(*argv, "/") == 0)
		{
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisior\n");
		}
		else /* must be number or invalid command */
		{
			if (getfloat(*argv, &op2) == -1)
			{
				printf("error: invalid command %s\n", *argv);
				return -1;
			}
			push(op2);
		}
	}

	printf("\t%.8g\n", pop());
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

/* getfloat: convert string s to float *pf. Return -1 if not a number */
int getfloat(char *s, double *pf)
{
	double sign, pow = 1.0;

	/* skip white spaces */
	while (isspace(*s))
		s++;

	if (!isdigit(*s) && *s != '-' && *s != '+')
		return -1;

	sign = (*s == '-') ? -1.0 : 1.0;
	if (*s == '-' || *s == '+')
		++s;
	for (*pf = 0.0; isdigit(*s); ++s)
		*pf = 10.0 * *pf + (*s - '0');

	if (*s == '.')
	{
		for (++s; isdigit(*s); ++s)
		{
			*pf = 10.0 * *pf + (*s - '0');
			pow *= 10.0;
		}
	}

	*pf = *pf * sign / pow;
	return 0;
}

#include <stdio.h>
#include <string.h>

#define MAXLEN 100

void push(double);
double pop(void);

int main(void)
{
	char c, s[MAXLEN];
	char *p;
	double op1, op2;

	while (scanf("%s%c", s, &c) == 2)
	{
		if (sscanf(s, "%lf", &op1) == 1) /* it's a number */
			push(op1);
		else /* one or more operators */
		{
			for (p = s; *p; ++p)
			{
				switch(*p)
				{
					case '+':
						push(pop() + pop());
						break;
					case '-':
						op2 = pop();
						push(pop() - op2);
						break;
					case '*':
						push(pop() * pop());
						break;
					case '/':
						op2 = pop();
						if (op2 == 0.0)
							printf("error: division"
							       " by zero\n");
						else
							push(pop() / op2);
						break;
					default:
						printf("unknown command\n");
						break;
				}
			}
			if (c == '\n')
				printf("\t%.8g\n", pop());
		}
	}

	return 0;
}

#define STACKSIZE 100
static double stack[STACKSIZE];
static int pos = 0;

/* push: push val onto value stack */
void push(double val)
{
	if (pos < STACKSIZE)
		stack[pos++] = val;
	else
		printf("error: stack full for push()\n");
}

/* pop: return last pushed valued from stack */
double pop(void)
{
	if (pos > 0)
		return stack[--pos];
	else
	{
		printf("error: stack empty for pop()\n");
		return 0.0;
	}
}

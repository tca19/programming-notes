#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...)
{
	va_list ap;
	char *p;
	int *ival;
	double *dval;

	va_start(ap, fmt);
	for (p = fmt; *p; ++p)
	{
		if (*p != '%')
			continue;
		switch(*++p)
		{
			case 'd': case 'i':
				ival = va_arg(ap, int *);
				scanf("%d", ival);
				break;
			case 'f': case 'g': case 'e':
				dval = va_arg(ap, double *);
				scanf("%lf", dval);
				break;
			default:  /* do nothing if not integer or double */
				break;
		}
	}
}

int main(void)
{
	int i;
	double f;

	minscanf("%i %f", &i, &f);
	printf("int: %d; double: %g\n", i, f);
	return 0;
}

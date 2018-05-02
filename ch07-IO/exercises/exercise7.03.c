#include <stdio.h>
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap; /* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;
	unsigned int uval;

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; ++p)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}
		switch (*++p)
		{
			case 'd': case 'i':
				ival = va_arg(ap, int);
				printf("%d", ival);
				break;
			case 'o':
				uval = va_arg(ap, unsigned int);
				printf("%o", uval);
				break;
			case 'x':
				uval = va_arg(ap, unsigned int);
				printf("%x", uval);
				break;
			case 'X':
				uval = va_arg(ap, unsigned int);
				printf("%X", uval);
				break;
			case 'u':
				uval = va_arg(ap, unsigned int);
				printf("%u", uval);
				break;
			case 'c':
				ival = va_arg(ap, int);
				printf("%c", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f", dval);
				break;
			case 'e': case 'E':
				dval = va_arg(ap, double);
				printf("%e", dval);
				break;
			case 'g': case 'G':
				dval = va_arg(ap, double);
				printf("%g", dval);
				break;
			case 's':
				for (sval = va_arg(ap, char *); *sval; ++sval)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}

int main(void)
{
	printf("Number 158 in different format :\n");
	minprintf("%%x: %x\n", 158);
	minprintf("%%X: %X\n", 158);
	minprintf("%%o: %o\n", 158);
	minprintf("%%e: %e\n", 158.0);
	minprintf("%%G: %G\n", 158.0);
	minprintf("%%i: %i\n", 158);
	return 0;
}

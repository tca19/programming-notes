#include <ctype.h>
#include <stdio.h>

/* atof: convert string s to double, handle scientific notation */
double atof(char s[])
{
	double val, power, power_e;
	int i, sign, exponent;

	/* skip white space */
	for (i = 0; s[i] == ' ' || s[i] == '\t'; ++i)
		;

	/* handle (optional) sign */
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;

	/* get integer part */
	for (val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');

	/* get decimal part */
	if (s[i] == '.') ++i;
	for (power = 1.0; isdigit(s[i]); ++i)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	/* get scientific notation part */
	if (s[i] == 'e' || s[i] == 'E') ++i;

	/* we divide val by power; since E-1 divides by 10, therefore we need to
	 * multiply power by 10 if there is a '-' */
	power_e = (s[i] == '-') ? 10 : 0.1;
	if (s[i] == '-' || s[i] == '+') ++i;

	for (exponent = 0; isdigit(s[i]); ++i)
		exponent = 10 * exponent + (s[i] - '0');
	while (exponent-- > 0)
		power *= power_e;

	return sign * val / power;
}

int main()
{
	char s1[] = "	6.022E23";
	char s2[] = " 6.022e23";
	char s3[] = " 6.022e-02";
	char s4[] = " 6.022e+02";
	char s5[] = "-123";
	char s6[] = "0.00167";

	printf("s1: %s\t\tatof(s1): %g\n", s1, atof(s1));
	printf("s2: %s\t\tatof(s2): %g\n", s2, atof(s2));
	printf("s3: %s\t\tatof(s3): %g\n", s3, atof(s3));
	printf("s4: %s\t\tatof(s4): %g\n", s4, atof(s4));
	printf("s5: %s\t\tatof(s5): %g\n", s5, atof(s5));
	printf("s6: %s\t\tatof(s6): %g\n", s6, atof(s6));
	return 0;
}

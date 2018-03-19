#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version */

float fahr_to_celsius(float temp)
{
	return 5*(temp-32)/9.0;
}

int main()
{
	float fahr;
	int lower, upper, step;

	lower = 0;    /* lower limit of temperature table */
	upper = 300;  /* upper limit */
	step = 20;    /* step size */

	fahr = lower;
	for (fahr = lower; fahr <= upper; fahr += step)
		printf("%3.0f %6.1f\n", fahr, fahr_to_celsius(fahr));

	return 0;
}

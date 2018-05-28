#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; with header */
int main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;    /* lower limit of temperature table */
	upper = 300;  /* upper limit */
	step = 20;    /* step size */

	/* print heading of table */
	printf(" %14s | %16s\n", "Celsius (°C)", "Fahrenheit (°F)");
	printf("=================================\n");

	celsius = lower;
	while (celsius <= upper) {
		fahr = 9.0/5.0 * celsius + 32.0;

		printf(" %8.0f      | %9.0f\n", celsius, fahr);
		celsius += step;
	}

	return 0;
}

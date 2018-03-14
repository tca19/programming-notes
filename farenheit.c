#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version */
main()
{
	/*int fahr, celsius;*/
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;    /* lower limit of temperature table */
	upper = 300;  /* upper limit */
	step = 20;    /* step size */

	fahr = lower;
	while (fahr <= upper) {
		celsius = 5 * (fahr-32) / 9;

		/* %3d = right aligned, 3 char long */
		/*printf("%3d %6d\n", fahr, celsius);*/

		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}

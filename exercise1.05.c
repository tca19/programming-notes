#include <stdio.h>

/* print Fahrenheit-Celsius table for fahr = 300, 280, ..., 0 with header and
 * for loop */
int main()
{
	int fahr;

	/* print heading of table */
	printf(" %16s | %16s\n", "Fahrenheit (°F)", "Celsius (°C)");
	printf("======================================\n");

	for (fahr = 300; fahr >= 0; fahr -= 20)
		printf(" %10d      | %12.1f\n", fahr, (5.0/9.0)*(fahr-32.0));

	return 0;
}

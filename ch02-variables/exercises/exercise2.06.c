#include <stdio.h>

/* setbits: set the n bits starting at position p in x to the n rightmost bits
 *          of y. Return x. */
unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
	x = ~(~(~0 << n) << (p-n+1)) & x; /* sets appropriate bits to 0 */
	y = ~(~0 << n) & y;  /* keep only n rightmost bits of y */
	y = y << (p-n+1);    /* move these bits to appropriate location */
	return x | y;
}

int main()
{
    int x = 3;
    int y = 15;
    printf("%u\n", setbits(x, 10, 4, y));
    return 0;
}

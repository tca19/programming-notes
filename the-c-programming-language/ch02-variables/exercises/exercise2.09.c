#include <stdio.h>

/* Explain why x &= (x-1) deletes the rightmost 1-bit in x
 *
 * If the rightmost bit of x is 1, then (x-1) is the exact same number as x
 * except that the rightmost bit is now 0. And since 1 & 0 = 0, after x &=
 * (x-1), the rightmost bit of x is now 0. The statement has indeed deleted the
 * rightmost 1-bit of x.
 *
 * If the rightmost bit of x is 0, then (x-1) has the rightmost bit set to 1,
 * and the rightmost 1-bit set to 0 (because -1). So x & (x-1) will leave the
 * rightmost bit to 1, and set the rightmost 1-bit to 0. Other bits are
 * unchanged because either (x-1) does not modify them (and _ & _ = _ ) or the
 * 0 in x have become 1 in (x-1) and 0 & 1 = 0. The statement has also deleted
 * the rightmost 1-bit in x.
 */

/* bitcount_fast: count number of 1-bit in x */
int bitcount_fast(unsigned int x)
{
	int b;

	for (b = 0; x > 0; x &= (x-1))
		++b;

	return b;
}

int main()
{
	int x = 63;
	printf("x: %d\nnumber of 1-bit in x: %d\n", x, bitcount_fast(x));
	return 0;
}

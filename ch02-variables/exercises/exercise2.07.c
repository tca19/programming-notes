#include <stdio.h>
#define MAX_BIT_SIZE 32

/* invert: flip (XOR 1) the n bits of x starting at position p */
unsigned int invert(unsigned int x, int p, int n)
{
	return x ^ ~(~0<< n) << (p-n+1);
}

/* print_as_binary: print the binary string representing x */
void print_as_binary(unsigned int x)
{
	int i;
	char bits[MAX_BIT_SIZE+1];
	printf("x: %u, bin(x): ", x);

	for (i = MAX_BIT_SIZE-1; i > -1; --i)
	{
		if (x & 1)
			bits[i] = '1';
		else
			bits[i] = '0';
		x >>= 1;
	}

	bits[MAX_BIT_SIZE] = '\0';
	printf("%s\n", bits);
}

int main()
{
	int x = 1468810422;
	int p = 20;
	int n = 5;

	printf("before:\n");
	print_as_binary(x);
	printf("after invert(x, %d, %d)\n", p, n);
	print_as_binary(invert(x, p, n));

	return 0;
}


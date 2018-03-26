#include <stdio.h>
#define MAX_BIT_SIZE 32

/* rightrot: rotate x by n bit positions to the right */
unsigned int rightrot(unsigned int x, int n)
{
	unsigned int right = ~(~0 << n) & x;
	unsigned int left  =  (~0 << n) & x;
	return (right << (MAX_BIT_SIZE-n)) | (left >> n);
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
	int n = 12;

	printf("before:\n");
	print_as_binary(x);
	printf("after rightrot(x, %d)\n", n);
	print_as_binary(rightrot(x, n));

	return 0;
}


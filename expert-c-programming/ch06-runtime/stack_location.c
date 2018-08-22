#include <stdio.h>

int x = 1;

/* factorial: return the factorial of n */
int factorial(int n)
{
	return (n < 2) ? 1 : n * factorial(n-1);
}

int main()
{
	int y = 0;
	int ar[1000] = {0};
	y = factorial(15);

	printf("The stack top is near:\t\t %p\n", &y);
	printf("The data segment top is near:\t %p\n", &x);
	printf("Address of main():\t\t %p\n", &main);
	printf("Address of factorial():\t\t %p\n", &factorial);
	return 0;
}

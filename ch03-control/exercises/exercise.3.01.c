#include <stdio.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]. Only one test in the
 * while() loop. */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = mid = 0;
	high = n-1;
	while (low <= high && v[mid] != x)
	{
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}

	return (v[mid] == x) ? mid : -1;
}

int main()
{
	int x = 7;
	int v[10] = {-9, -3, -1, 0, 2, 3, 7, 8, 10, 15};

	printf("x: %d\npos of x in v: %d\n", x, binsearch(x, v, 10));
	return 0;
}

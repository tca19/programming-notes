#include <stdio.h>

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n-1;
	while (low <= high)
	{
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (v[mid] < x)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int v[] = {-2, 0, 5, 18};
	int x = -2;
	printf("position of %d: %d\n", x, binsearch(x, v, 4));

	return 0;
}

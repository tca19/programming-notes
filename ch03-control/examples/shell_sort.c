#include <stdio.h>

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap)
			{
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

int main()
{
	int i;
	int ar[] = {1, -6, 5, -2, 10, 22, -7, -13, 2, 5};
	shellsort(ar, 10);

	for (i = 0; i < 10; ++i)
		printf("%d%c", ar[i], (i == 9) ? '\n' : ' ');

	return 0;
}

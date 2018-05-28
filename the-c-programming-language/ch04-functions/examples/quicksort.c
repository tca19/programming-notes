#include <stdio.h>

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
	int i, last;
	void swap(int v[], int i, int j);

	if (left >= right)    /* do nothing if less than two elements */
		return;

	swap(v, left, (left+right)/2); /* choose middle element as pivot, move */
	last = left;                   /* it in v[0] */
	for (i = left+1; i <= right; ++i)
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);          /* restore partition elem */
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int main()
{
	int i;
	int ar[10] = {1, -6, 3, 1, -16, 2, 8, 4, 9};

	for (i = 0; i < 10; ++i)
		printf("%d%c", ar[i], (i == 9) ? '\n' : ' ');

	qsort(ar, 0, 9);

	for (i = 0; i < 10; ++i)
		printf("%d%c", ar[i], (i == 9) ? '\n' : ' ');

	return 0;
}

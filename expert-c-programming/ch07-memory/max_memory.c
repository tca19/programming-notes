#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int Mb = 0;
	while ( malloc(1<<20) ) ++Mb;
	printf("Allocated %d Mb total\n", Mb);
}

#include <stdio.h>
#include <limits.h>

/* find ranges of char, short, int and long variables */
int main()
{
	printf("signed\n======\n");
	printf("  - char:  MIN=%d	MAX=%d\n", CHAR_MIN, CHAR_MAX);
	printf("  - short: MIN=%d	MAX=%d\n", SHRT_MIN, SHRT_MAX);
	printf("  - int:   MIN=%d	MAX=%d\n", INT_MIN, INT_MAX);
	printf("  - long:  MIN=%ld	MAX=%ld\n", LONG_MIN, LONG_MAX);

	printf("unsigned\n========\n");
	printf("  - char:  MIN=%d	MAX=%d\n", 0, UCHAR_MAX);
	printf("  - short: MIN=%d	MAX=%d\n", 0, USHRT_MAX);
	printf("  - int:   MIN=%d	MAX=%u\n", 0, UINT_MAX);
	printf("  - long:  MIN=%d	MAX=%lu\n", 0, ULONG_MAX);

	return 0;
}

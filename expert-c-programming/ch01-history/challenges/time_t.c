#include <stdio.h>
#include <time.h>

#define MAXLEN 80

int main(void)
{
	time_t biggest, now;
	long duration;
	char s[MAXLEN];

	biggest = 0x7FFFFFFF;
	time(&now);

	printf("Max time_t (local): %s", ctime(&biggest));
	printf("Max time_t (UTC):   %s\n", asctime(gmtime(&biggest)));

	duration = (long) difftime(biggest, now);
	printf("The person who removed the comment will still be cursed for\n");

	printf("  - %2ld years\n", duration/(3600*24*365));
	duration %= (3600*24*365);
	printf("  - %2ld months\n", duration/(3600*24*30));
	duration %= (3600*24*30);
	printf("  - %2ld days\n", duration/(3600*24));
	duration %= (3600*24);
	printf("  - %2ld hours\n", duration/(3600));
	duration %= (3600);
	printf("  - %2ld minutes\n", duration/(60));
	duration %= (60);
	printf("  - %2ld seconds\n", duration);

	return 0;
}

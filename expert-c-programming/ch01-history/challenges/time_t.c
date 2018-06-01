#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t biggest, current;
	double duration;
	char s[100];

	biggest = 0x7FFFFFFF;
	current = time(NULL);

	printf("Max time_t (local): %s", ctime(&biggest));
	printf("Max time_t (UTC):   %s", asctime(gmtime(&biggest)));

	duration = difftime(biggest, current);
	printf("Has to be cursed for %f seconds (~%f days)\n",
	       duration, duration/86400);

	return 0;
}

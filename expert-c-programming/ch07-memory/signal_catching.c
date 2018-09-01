#include <stdio.h>
#include <signal.h>
#include <unistd.h> /* pause() */

void catch_CTRL_break(int sig)
{
	printf("You pressed CTRL^C, but you can't escape!\n");
}

int main(void)
{
	char input;
	signal(SIGINT, catch_CTRL_break);

	printf("Try to exit this program.\n");
	while ((input = getchar()))
		if (input == 'q')
			break;

	return 0;
}

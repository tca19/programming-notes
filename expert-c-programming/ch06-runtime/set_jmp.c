#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int banana()
{
	printf("in banana()\n");
	longjmp(buf, 1);

	printf("you'll never see this, because I longjmp'd");
}

int main(void)
{
	if (setjmp(buf))
		printf("back in main\n");
	else
	{
		printf("first time through\n");
		banana();
	}
}

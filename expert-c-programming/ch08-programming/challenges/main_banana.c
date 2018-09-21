#include "banana_peel.c"

void banana_peel(char a, short b, float c);

/* next line will cause compile error because function declaration does not
 * match function definition */
/* void banana_peel(char a, char b, float c) */

int main(void)
{
	banana_peel('a', 16, 2.2);
}


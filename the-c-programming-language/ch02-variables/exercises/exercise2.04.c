#include <stdio.h>

/* squeeze: delete each character in s1 that is also in s2 */
void squeeze(char s1[], char s2[])
{
	int i, j, k;

	for (i = j = 0; s1[i] != '\0'; ++i)
	{
		for (k = 0; s2[k] != '\0' && k > -1; ++k)
			if (s1[i] == s2[k])
				k = -2; /* set to -2 because ++k in the loop */

		/* means no premature exit of previous loop, can add letter */
		if (k > -1)
			s1[j++] = s1[i];
	}

	s1[j] = '\0';
	return;
}

int main()
{
	char s1[] = "hello world";
	char s2[] = "abcde";
	printf("s1: %s\ns2: %s\n", s1, s2);
	squeeze(s1, s2);
	printf("s1-s2:%s\n", s1);
	return 0;
}

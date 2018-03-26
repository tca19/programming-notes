#include <stdio.h>

/* any: return first location of any s2 character in s1, -1 if none */
int any(const char *s1, const char *s2)
{
	int i, j;

	for (i = 0; s1[i] != '\0'; ++i)
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				return i;

	return -1;
}

int main()
{
	char *s1 = "building";
	char *s2 = "under";
	printf("s1: %s\ns2: %s\n", s1, s2);
	printf("pos: %d\n", any(s1, s2));
	return 0;
}


#include <stdio.h>

/* htoi: convert a string of hexadecimal digits into its equivalent integer */
unsigned long htoi(char s[])
{
	int i;
	unsigned long n;
	i = 0;

	/* optional 0x or 0X prefix, skip it */
	if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))
		i += 2;

	for (n = 0; s[i] != '\0'; ++i)
		if (s[i] >= '0' && s[i] <= '9')
			n = n * 16 + (s[i] - '0');
		else if (s[i] >= 'a' && s[i] <= 'f')
			n = n * 16 + (s[i] - 'a' + 10);
		else if (s[i] >= 'A' && s[i] <= 'F')
			n = n * 16 + (s[i] - 'A' + 10);

	return n;
}

int main()
{
	char s[] = "0xacdef182";
	printf("%lu\n", htoi(s));
	return 0;
}

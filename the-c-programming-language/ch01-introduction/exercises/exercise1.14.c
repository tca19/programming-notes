#include <stdio.h>

/* print a histogram of the frequencies of different characters in input */
int main()
{
	int nletter[26], ndigit[10];
	int nother, i, c;
	float nchar, freq;

	for (i = 0; i < 26; ++i)
		nletter[i] = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	nother = nchar = 0;
	while ((c = getchar()) != EOF)
	{
		++nchar;
		if (c >= 'a' && c <= 'z')
			++nletter[c-'a'];
		else if (c >= 'A' && c <= 'Z')
			++nletter[c-'A'];
		else if (c >= '0' && c <= '9')
			++ndigit[c-'0'];
		else
			++nother;
	}

	printf("Character | Frequency | (+ <=> 1%%)\n");
	printf("=======================\n");

	/* letters histogram */
	for (i = 0; i < 26; ++i)
	{
		if (nletter[i] > 0)
		{
			freq = nletter[i]*100 / nchar;
			printf("%6c    | % 7.2f%%  | ", 'a'+i, freq);
			while (freq > 0)
			{
				putchar('+');
				freq -= 1.0;
			}
			putchar('\n');
		}
	}

	/* digits histogram */
	putchar('\n');
	for (i = 0; i < 10; ++i)
	{
		if (ndigit[i] > 0)
		{
			freq = ndigit[i]*100 / nchar;
			printf("%6c    | % 7.2f%%  | ", '0'+i, freq);
			while (freq > 0)
			{
				putchar('+');
				freq -= 1.0;
			}
			putchar('\n');
		}
	}

	/* symbol histogram */
	putchar('\n');
	if (nother > 0)
	{
		freq = nother*100 / nchar;
		printf("   OTHER  | % 7.2f%%  | ", freq);
		while (freq > 0)
		{
			putchar('+');
			freq -= 1.0;
		}
		putchar('\n');
	}

	return 0;
}

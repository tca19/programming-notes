#include <stdio.h>
#define MAX_LENGTH 50

/* print a histogram of the lengths of words in input */
int main()
{
	int count[MAX_LENGTH];
	int c, i, length, in_word;

	for (i = 0; i < MAX_LENGTH; ++i)
		count[i] = 0;

	length = 0;
	in_word = 0;
	while ((c = getchar()) != EOF)
	{
		if (c == ' ' || c == '\n' || c == '\t')
		{
			if (in_word) /* word ended, increment count of its length */
			{
				if (length > MAX_LENGTH) /* crop long words */
					length = MAX_LENGTH;

				++count[length-1];
				length = 0;
				in_word = 0;
			}
		}
		else
		{
			in_word = 1;
			++length;
		}
	}

	printf("Length | Count |\n");
	printf("================\n");
	for (i = 0; i < MAX_LENGTH; ++i)
	{
		if (count[i] > 0)
		{
			printf("% 4d   | % 4d  | ", i+1, count[i]);
			while (count[i]--)
				printf("+");

			printf("\n");
		}
	}

	return 0;
}

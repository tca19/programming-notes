#include <stdio.h>
#define MAXLENGTH 1000


void reverse(char s[], int length);
int getline(char line[], int LIM);

/* reverse each line of input */
int main()
{
	int length;
	char line[MAXLENGTH];

	while ((length = getline(line, MAXLENGTH)) > 0)
	{
		reverse(line, length);
		printf("%s", line);
	}

	return 0;
}

/* reverse the string `s`, in place */
void reverse(char s[], int length)
{
	int i;
	char c;

	/* do not reverse last char if its \0 or \n */
	if (s[length-1] == '\0')
		--length;

	if (s[length-1] == '\n')
		--length;

	for (i = 0; i < length/2; ++i)
	{
		c = s[i];
		s[i] = s[length-1-i];
		s[length-1-i] = c;
	}
}

/* getline: read a line from input to `line`, return its length */
int getline(char line[], int LIM)
{
	int c, l;

	l = 0;
	while (l < LIM-1 && (c = getchar()) != EOF && c != '\n')
		line[l++] = c;
	if (c == '\n')
		line[l++] = c;

	line[l] = '\0';
	return l;
}

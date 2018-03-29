#include <stdio.h>
#define MAXLENGTH 200

/* escape: copies t to s but converts newlines to \n, tabs to \t and
 * spaces as _ */
void escape(char s[], char t[])
{
	int i, j;

	for (i = 0, j = 0; t[i] != '\0'; ++i)
		switch (t[i])
		{
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			case ' ':
				s[j++] = '_';
				break;
			default:
				s[j++] = t[i];
				break;
		}
	s[j] = '\0';
}

int main()
{
	char s[MAXLENGTH];
	char t[] = "hello\t\tworld\n this is \texercise\n\n# 2";

	printf("-- Original :\n%s\n", t);
	escape(s, t);
	printf("-- Escaped :\n%s\n", s);

	return 0;
}


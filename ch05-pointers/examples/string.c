/* strcpy_a: copy s to t; array subscript version */
void strcpy_a(char *s, char *t)
{
	int i;
	for (i = 0; ((t[i] = s[i]) != '\0'); ++i)
		;
}

/* strcpy_p: copy s to t; pointer version */
void strcpy_p(char *s, char *t)
{
	while ((*t = *s) != '\0')
	{
		++s;
		++t;
	}
}

/* strcpy: copy s to t: pointer version 2 */
void strcpy(char *s, char *t)
{
	while ((*t++ = *s++) != '\0')
		;
}

/* strcmp_a: return <0 if s<t, 0 if s==t, >0 if s>t: array subscript version */
int strcmp_a(char *s, char *t)
{
	int i;

	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}

/* strcmp_p: return <0 if s<t, 0 if s==t, >0 if s>t: pointer version */
int strcmp_p(char *s, char *t)
{
	while (*s++ == *t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

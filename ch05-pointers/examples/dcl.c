#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int etc.. */
char out[1000];          /* output string */

int main()  /* convert declaration to words */
{
	while (gettoken() != EOF)
	{
		strcpy(datatype, token); /* 1st token on line is datatype */
		out[0] = '\0';
		dcl();                   /* parse rest of line */
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )  /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{

	int type;

	if (tokentype == '(')          /* ( dcl ) */
	{
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	}
	else if (tokentype == NAME)    /* variable name */
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while ((type = gettoken()) == PARENS || type = BRACKETS)
		if (type == PARENS)
			strcat(out, " function returnning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct tnode              /* the tree node: */
{
	char *word;            /* points to the text */
	int count;             /* number of occurrences */
	struct tnode *lchild;  /* left child */
	struct tnode *rchild;  /* right child */
};

#define MAXLEN 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main(void)
{
	struct tnode *root;
	char word[MAXLEN];

	root = NULL;
	while (getword(word, MAXLEN) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL)          /* a new word has arrived */
	{
		p = talloc();   /* make a new node */
		p->word  = strdup(w);
		p->count = 1;
		p->lchild = p->rchild = NULL;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;     /* repeated word */
	else if (cond < 0)      /* less than into left subtree */
		p->lchild = addtree(p->lchild, w);
	else                    /* greater than into the right subtree */
		p->rchild = addtree(p->rchild, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL)
	{
		treeprint(p->lchild);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->rchild);
	}
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int getword(char *word, int lim)
{
	int c, getchar(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getchar()));

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}

	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getchar()))
		{
			ungetch(*w);
			break;
		}

	*w = '\0';
	return w[0];
}

#define BUFSIZE 100

char buffer[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;           /* next free position in buffer */

int getch(void)      /* get a (possibly) pushed back character */
{
	if (bufp > 0)
		return buffer[--bufp];
	return getchar();
}

void ungetch(int c)    /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("error: ungetch() buffer is full.\n");
	else
		buffer[bufp++] = c;
}

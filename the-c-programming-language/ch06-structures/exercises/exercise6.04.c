#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLEN 100

struct tnode
{
	char *word;
	int count;
	struct tnode *lchild;
	struct tnode *rchild;
};

int get_word(char *, int);
struct tnode *add_node(struct tnode *, char *, int *);
struct tnode **fill_array(struct tnode **, struct tnode *);
int cmp_occurrence(const void *a, const void *b);

/* print words from input by decreasing number of occurrences */
int main(void)
{
	struct tnode *root;
	struct tnode **ar;
	char word[MAXLEN];
	int nwords;

	root = NULL;
	nwords = 0;

	/* count occurrence of each word and total number of different words */
	while (get_word(word, MAXLEN) != EOF)
		if (isalpha(word[0]))
			root = add_node(root, word, &nwords);

	/* store nodes in array, sort by decreasing number of occurrence */
	ar = malloc(nwords * sizeof *ar);
	fill_array(ar, root);
	qsort(ar, nwords, sizeof *ar, cmp_occurrence);

	/* print sorted words */
	for (; nwords-- > 0; ++ar)
		printf("%4d %s\n", (*ar)->count, (*ar)->word);

	return 0;
}

/* get_word: read a word from input, return word[0] or EOF */
int get_word(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()));

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()))
		{
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

struct tnode *talloc(void);
char *strdup(char *);

/* add_node: add word to tree p or increment its counter if already present */
struct tnode *add_node(struct tnode *p, char *w, int *nwords)
{
	int cond;

	if (p == NULL)
	{
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->lchild = p->rchild = NULL;
		(*nwords)++;
	}
	else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->lchild = add_node(p->lchild, w, nwords);
	else
		p->rchild = add_node(p->rchild, w, nwords);
	return p;
}

/* fill_array: put each tnode pointer of tree into array ar */
struct tnode **fill_array(struct tnode **ar, struct tnode *tree)
{
	if (tree != NULL)
	{
		*ar = tree;
		ar++;
		ar = fill_array(ar, tree->lchild);
		ar = fill_array(ar, tree->rchild);
	}
	return ar;
}

/* cmp_occurrence: compare a and b by number of occurrence.
 *                 Return b.count - a.count to get decreasing order. */
int cmp_occurrence(const void *a, const void *b)
{
	return (*(struct tnode **)b)->count - (*(struct tnode **)a)->count;
}

/* talloc: allocate memory for storing a tnode element */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: duplicate string s */
char *strdup(char *s)
{
	char *t;
	t = (char *) malloc(strlen(s)+1);
	if (t != NULL)
		strcpy(t, s);
	return t;
}

#define BUFSIZE 1000
int buffer[BUFSIZE];
int bufp = 0;

/* getch: read a character from buffer or stdin */
int getch(void)
{
	return (bufp > 0) ? buffer[--bufp] : getchar();
}

/* ungetch: put back character c into buffer */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("error: ungetch() buffer is full.\n");
	else
		buffer[bufp++] = c;
}

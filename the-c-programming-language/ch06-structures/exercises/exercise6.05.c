#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

/* hash: produce hashtab index from string */
unsigned int hash(char *s)
{
	unsigned int hashval;

	for (hashval = 0; *s != '\0'; ++s)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* strdup: duplicate string s */
char *strdup(char *s)
{
	char *t;

	t = malloc(strlen(s)+1);
	if (t != NULL)
		strcpy(t, s);
	return t;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *p;

	for (p = hashtab[hash(s)]; p != NULL; p = p->next)
		if (strcmp(s, p->name) == 0)
			return p;
	return NULL;
}

/* install: add (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *p;
	unsigned int hashval;

	if ((p = lookup(name)) == NULL) /* not already here */
	{
		p = malloc(sizeof(*p));
		hashval = hash(name);
		p->next = hashtab[hashval];
		p->name = strdup(name);
		hashtab[hashval] = p;
	}
	else /* remove previous defn value for update */
		free((void *) p->defn);

	p->defn = strdup(defn);
	return p;
}

/* undef; remove name if present in hashtab */
void undef(char *name)
{
	struct nlist *p, *p_prev;
	unsigned int hashval;

	for (p = hashtab[hashval = hash(name)], p_prev = NULL;
	     p != NULL;
	     p_prev = p, p = p->next)
		if (strcmp(name, p->name) == 0)
		{
			/* 2 cases : first elem of linked list , or not */
			if (p_prev == NULL)
				hashtab[hashval] = p->next;
			else
				p_prev->next = p->next;

			free(p->name);
			free(p->defn);
			free(p);
			break;
		}
}

/* print_hashtab: print all (name, defn) stored in hashtab */
void print_hashtab()
{
	struct nlist *p;
	int i;

	for (i = 0; i < HASHSIZE; ++i)
		for (p = hashtab[i]; p != NULL; p = p->next)
			printf("%s -> %s\n", p->name, p->defn);
}

int main()
{
	install("IN", "1");
	install("HASHSIZE", "101");
	install("HASHSIZE", "1001");
	undef("IN");
	print_hashtab();
	return 0;
}

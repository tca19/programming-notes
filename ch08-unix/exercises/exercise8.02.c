#include <unistd.h>
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20

struct flags
{
	unsigned int _READ  : 1;
	unsigned int _WRITE : 1;
	unsigned int _UNBUF : 1;
	unsigned int _EOF   : 1;
	unsigned int _ERR   : 1;
};

typedef struct _iobuf
{
	char *ptr;
	char *base;
	struct flags status;
	int fd;
	int cnt;
} FILE;
FILE _iob[OPEN_MAX];

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)    ((p)->status._EOF == 1)
#define ferror(p)  ((p)->status._ERR == 1)

#define getc(p)    (--(p)->cnt >= 0 \
		   ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 \
		   ? *(p)->ptr++ = (x) : _flushbuf(x, p))

#define getchar()  getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666

/* fopen: open file, return FILE ptr, use bit fields for status flags */
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->status._READ == 0 || fp->status._WRITE == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL; /* no free slot found */

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a')
	{
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1) /* can't open file */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r')
		fp->status._READ = 1;
	else
		fp->status._WRITE = 1;
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->status._EOF == 1 || fp->status._ERR == 1)
		return EOF;
	bufsize = (fp->status._UNBUF == 1) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0)
	{
		if (fp->cnt == -1)
			fp->status._EOF = 1;
		else
			fp->status._ERR = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* test fopen and _fillbuf functions, read 100 first characters of a file */
int main(void)
{
	int i;
	char text[100];
	FILE *f;

	f = fopen("exercise8.02.c", "r");
	for (i = 0; i < 100; ++i)
		text[i] = getc(f);

	write(0, text, 100);
	return 0;
}

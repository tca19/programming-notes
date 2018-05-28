#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      /* flags for read and write */
#include <sys/stat.h>   /* structure returned by stat */
#include <sys/types.h>  /* typedefs */
#include "dirent.h"

void fsize(char *);

int main(int argc, char **argv)
{
	if (argc == 1)  /* default: current directory */
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file "name" */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAXPATH 1024
#define DIRSIZ  14
DIR_ *opendir_(char *dirname);
Dirent *readdir_(DIR_ *dfd);
void closedir_(DIR_ *dfd);

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAXPATH];
	Dirent *dp;
	DIR_ *dfd;

	if ((dfd = opendir_(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir_(dfd)) != NULL)
	{
		if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
			continue; /* skip self and parent */
		if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
			        dir, dp->name);
		else
		{
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	closedir_(dfd);
}

int fstat(int fd, struct stat *);

/* opendir: open a directory for readdir calls */
DIR_ *opendir_(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIR_ *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
	 || fstat(fd, &stbuf) == -1
	 || (stbuf.st_mode & S_IFMT) != S_IFDIR
	 || (dp = (DIR_ *) malloc(sizeof(DIR_))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/* closedir: close directory opened by opendir */
void closedir_(DIR_ *dp)
{
	if (dp)
	{
		close(dp->fd);
		free(dp);
	}
}

#include <sys/dir.h>    /* local directory structure */

/* readdir: read directory entries in sequence */
Dirent *readdir_(DIR_ *dp)
{
	struct direct dirbuf; /* local directory structure */
	static Dirent d;      /* return: portable structure */

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
	{
		if (dirbuf.d_ino == 0) /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; /* ensure termination */
		return &d;
	}
	return NULL;
}

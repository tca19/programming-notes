#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 4096

/* cat: concatenate files (with POSIX system calls) */
int main(int argc, char *argv[])
{
	int fd, n;
	char buf[BUFSIZE];

	if (argc == 1)
		while ((n = read(0, buf, BUFSIZE)) > 0)
			write(1, buf, n);

	while (--argc > 0)
	{
		if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
		{
			fprintf(stderr, "error: can't open %s\n", *argv);
			return 1;
		}
		while ((n = read(fd, buf, BUFSIZE)) > 0)
			write(1, buf, n);
		close(fd);
	}
	return 0;
}

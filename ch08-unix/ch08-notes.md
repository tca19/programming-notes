The C programming language (K&R, 2nd edition)
=============================================

Chapter 8 : The UNIX System Interface
-------------------------------------

### 8.1 File Descriptors
In UNIX, all peripheral devices are files in the filesystem, so all IO is done
by reading/writing files.

When a program asks the OS to open a file, it returns a _file descriptor_ : an
integer to identify the file (like an ID, because easier to manage than the
filename).

When a program starts, 3 files are automatically opened : `stdin`, `stdout` and
`stderr` with respective file identifer 0, 1 and 2. When program input or output
are files (like `./a.out <file1 >file2`), the shell opends the files with file
identifer 0 for input and 2 for output. **Progam does not know if input comes
from keyboard or from file, only see it comes from file identifier 0 (same is
true for file identifier 1, whether it goes to screen of a file)**.

### 8.2 Low Level I/O - Read and Write
* `int read(int fd, char *buf, int n)` : read `n` bytes from files descriptor
  `fd` into character array `buf`, return number of read bytes
* `int write(int fd, char *buf, int n)` : read `n` bytes from `buf` to file
  descripor `fd`, return number of written bytes (if it's less than `n`, error
  occurred).

Large values of `n` => fewer system calls (functions above **are system
calls**). These two routines can be used to construct higher-level routines like
_unbuffered_ `getchar()` (with `n` set to 1) or _buffered_ `getchar()`.

Use `#undef` to overwrite a library function declared in a header with a macro
(like `#undef getchar`).

### 8.3 Open, Creat, Close, Unlink
To open files, 2 systems calls : ̣̣̣̣`open` and `creat`, both return a file
descriptor instead of FILE pointer and are contained in `#include <fnctl.h>`.
```C
#include <fnctl.h>
#define perms 0666 /* 9 bits of permission information for owner/group/other */

/* either O_RDONLY, O_WRONLY or O_RDWR */
int fd1 = open(name, O_RDONLY, perms); /* error if file name does not exist */
int fd2 = creat(name, perms); /* create file or re-write it */
```

Around 20 files can be opened simultaneously. If a program need to process more
than 20 files, it must close some files with `close (int fd)` (so this file
descriptor `fd` can be reused to open another file).

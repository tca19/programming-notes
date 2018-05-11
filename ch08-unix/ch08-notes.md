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
**Every functions here are in `#include <unistd.h>`.**

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
descriptor instead of FILE pointer and are contained in `#include <fcntl.h>`.
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

### 8.4 Random Access - Lseek
`long lseek(int fd, long offset, int origin)` : move current position in file
`fd` by `offset`relatively to `origin` (0 from beginning, 1 from current
position, 2 from end of file). Return the new position in file.

To append to a file, move to the end `lseek(fd, 0L, 2);` then use `write()`.
Standard library function is `fseek()`.

### 8.5 Example - An implementation of Fopen and Getc
A FILE structure (declared in `<stdio.h>`) is composed of :
* pointer to a buffer
* count of number of char left in buffer
* pointer to next char position in buffer
* file descriptor
* flags for permission, status...

Variable/function names in library **usually starts with _ to not collide**
with user's variable/function names.

`getc()` returns `(unsigned char)` to ensure that characters are positive.
`fopen()` uses `open()` to open file and set flags of FILE structure, but it
does not allocate storage for character buffer of FILE.

A FILE object uses a buffer to return characters when `getc()` is called but
when buffer is empty (like right after a FILE object is created), it calls
`_fillbuffer()` that calls `read()` to read some characters from file to buffer.

### 8.6 Example - Listing Directories
In UNIX, directories are **also files** that contain list of filenames and
location of each file (inode) so knowing the content of a directory is like
reading a file.

The program that prints the size of files in directories needs :
* a structure `Dirent` that contains filename and inode
* threed routines : `DIR *opendir(char *)`, `Dirent *readdir(DIR *)` and `void
  closedir(DIR *)`

`int stat(char *name, struct stat *st)` is a system function that reads the
information of file `name` and load it into structure `st` composed of device of
inode, inode, file size, modification/creation/access time... This `struct stat`
is declared in `<sys/stat.h>`, and uses types declared in `<sys/types.h>`.

Reading content of directory :
* `opendir()`
* call `readdir()` until getting `NULL`. It returns a directory entry `Dirent`
  (either a file or another directory)
* `closedir()`

### 8.7 Example - A Storage Allocator
`malloc()` will request space from OS as needed instead of using a fixed-size
array defined at compilation time. `malloc()` stores a linked list of _free
blocks_.  Each free block has : a size, a pointer to next free block and a free
space.

When a user requests a free space, first _large enough_ free block in the list
is used. It is split in two parts : one is unlinked from list and returned, the
other (remaining free space of the block) stays in linked list, but its size is
reduced. If no large enough block exists, `malloc()` asks the OS for another
large chunk of memory.

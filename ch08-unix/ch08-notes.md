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

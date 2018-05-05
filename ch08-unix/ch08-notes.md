The C programming language (K&R, 2nd edition)
=============================================

Chapter 8 : The UNIX System Interface
-------------------------------------

### 8.1 File Descriptors
In UNIX, all peripheral devices are files in the filesystem, so all IO is done
by reading/writing files.

When a program asks the OS to open a file, it returns a _file descriptor_ : an
integer to identify the file (like an ID).

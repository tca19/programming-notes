The C programming language (K&R, 2nd edition)
=============================================

Appendix B : Standard Library
-----------------------------

Not a part of C language, but define by ANSI standard (15 standard headers).

### B.1 Input and Output `<stdio.h>`
1/3 of the library. On UNIX, text streams and binary streams are identical.\
Stream = source or destination of data. When a program starts, 3 streams are
opened (`stdin`, `stdout`, `stderr`).\
In `fprintf`, the width/precision of the format string can be * : in that case
the value is computed by converting the next argument to `int`.

Common functions :
1. File operations
  * `FILE *fopen(const char *filename, const char *mode)`
  * `int fflush(FILE *stream)` : cause buffered unwritten data to be written
  * `FILE *tmpfile(void)` : create temp file of mode `wb+`, deleted when program
    terminates
2. Formatted output
  * `int fprintf(FILE *stream, const char *format, ...)` : return number of
    written characters, negative if an error occurred.
  * `int sprintf(char *s, const char *format, ...) : same as `fprintf` but write
    formatted output into `s`. Terminated `s` with `\0`.
3. Formatted input

The C programming language (K&R, 2nd edition)
=============================================

Appendix B : Standard Library
-----------------------------

Not a part of C language, but define by ANSI standard (15 standard headers).

### B.1 Input and Output `<stdio.h>`
1/3 of the library. On UNIX, text streams and binary streams are identical.\
Stream = source or destination of data. When a program starts, 3 streams are
opened (`stdin`, `stdout`, `stderr`).\
In `printf`, the width/precision of the format string can be * : in that case
the value is computed by converting the next argument to `int`.\
In `scanf`, a `*` skips one assignment (with `%*s`, no assignment is made).`%n`
assigns to the next argument the number of characters read so far.

Common functions :
1. File operations
  * `FILE *fopen(const char *filename, const char *mode)`
  * `int fflush(FILE *stream)` : cause buffered unwritten data to be written
  * `FILE *tmpfile(void)` : create temp file of mode `wb+`, deleted when program
    terminates
2. Formatted output
  * `int fprintf(FILE *stream, const char *format, ...)` : return number of
    written characters, negative if an error occurred.
  * `int sprintf(char *s, const char *format, ...)` : same as `fprintf` but
    write formatted output into `s`. Terminate `s` with `\0`.
3. Formatted input
  * `int fscanf(FILE *stream, const char *format, ...)` : assign converted
    values to each following argument, which must be **pointers**. Stop when
    `format` is exhausted, return number of items converted and assigned.
  * `int sscanf(char *s, const char *format, ...)`
4. Character input/output
  * `int fgetc(FILE *stream)` : return next character of `stream`
  * `char *fgets(char *s, int n, FILE *stream)` : read at most _n-1_ characters
    from _stream_ into `s`. Stop if `\n` is encountered.
  * `int fputc(char c, FILE *stream)`, `int fputs(const char *s, FILE *stream)`
    : write character `c` or string `s` on `stream`.
  * `int ungetc(int c, FILE *stream)` : replace character `c` onto `stream` so
    it will be returned on the next read.
5. Direct input/output
  * `size_t fread(void *ptr, size_t size, size_t nobj, FILE *stream)` : read
    from `stream` into array `ptr` at most `nobj` objects of size `size`.
  * `size_t fwrite(const void *ptr, size_t size, size_t nobj, FILE *stream)` :
    write `nobj` of size `size` from `ptr` to `stream`.
6. File positioning
  * `int fseek(FILE *stream, long offset, int origin)`
  * `int fgetpos(FILE *stream, fpos_t, *ptr)`, `int fsetpos(FILE *stream, const
    fpos_t *ptr)`

### B.2 Character Class Tests `<ctype.h>`
Contains many functions to test characters (`isalnum()`, `isdigit()`,
`isupper()`, `isspace()`...). They take and return an `int`. Contains also
`tolower()` and `toupper()`.

### B.3 String Functions `<string.h>`
1. Starting with **str**
  * `char *strcpy(s, ct)` : copy string `ct` to `s`. Return `s`.
  * `char *strcat(s, ct)` : concatenate string `ct` at the end of `s`. Return
    `s`.
  * `int strcmp(cs, ct)`
  * `char *strchr(cs, c)` : return pointer to first occurrence of `c` in `cs`.
  * `char *strstr(cs, ct)` : return pointer to first occurrence of string `ct`
    in string `cs`, `NULL` if none are present.
  * `char *strtok(s, ct)`
2. Starting with **mem** - to manipulate objects as character arrays
  * `void *memcpy(void *s, const void *ct, size_t n)` : copy `n` characters from
    `ct` to `s`.
  * `int memcmp(cs, ct, n)` : compare the first `n` characters of `cs` with
    `ct`.
  * `void *memset(void *s, int c, size_t n)` : place character `c` into first
    `n` characters of `s`. Return `s`.

### B.4 Mathematical Functions `<math.h>`
**Domain error** : argument is outside the domain over which the function is
defined.\
**Range errors** : result of the function cannnot be represented as a `double`.

Common functions : `sin()`, `asin()`, `sinh()` (same exists for cosine/tangent),
`log()` (natural logarithm), `log10()`, `fabs()`, `ldexp(x, n)` (x.2^n),
`fmod(x, y)` (remainder of x/y).

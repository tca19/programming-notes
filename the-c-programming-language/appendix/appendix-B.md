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

### B.5 Utility Functions `<stdlib.h>`
1. Number conversions
  * `double atof(const char *s)`, `int atoi(const char *s)`, `long(const char
    *s)` : respectively convert `s` to `double`, `int` and `long`.
  * `double strtod(const char *s, char **endp)`, `long strtol(const char *s,
    char **endp, int base)` : convert `s` to `double` or `long`, stores
    unconverted suffix in `endp` (only if `endp` is not `NULL`).
  * `int rand(void)` : return a random `int` between 0 and `RAND_MAX`. Seed can
    be initialized with `void srand(unsigned int seed)` (default is 1).
2. Memory allocation
  * `void *calloc(size_t nobj, size_t size)`
  * `void *malloc(size_t size)`
  * `void *realloc(void *p, size_t size)`
  * `void free(void *p)`
3. System and misc
  * `void exit(int status)` : cause normal program termination. `status` is
    returned to the environment. Can use `EXIT_SUCCESS` or `EXIT_FAILURE`.
  * `int system(const char *s)` : run command `s` by system.
  * `void *bsearch(const void *key, const void *base, size_t n, size_t size,
    int (*cmp)(const void *keyval, const void *datum))` : binary search of `key`
    inside sorted array `base`, which contains `n` elements of size `size`.
  * `void qsort(void *base, size_t n, size_t size, int (*cmp)(const void *,
    const void*))` : sort array `base` in **ascending order**.
  * `div_t div(x, y)` : return a struct containing `.quot (x/y)` and
    `.rem (x%y)`.

### B.6 Diagnostics `<assert.h>`
`void assert(int expression)` : if _expression_ is 0, error message + abortion
of program.

### B.7 Variable Argument Lists `<stdarg.h>`
To create functions with unknown number of arguments. Four steps inside such
functions :
* `va_list ap;`
* `va_start(va_list ap, lastarg);`
* `type va_arg(va_list ap, type);` : return a value of _type_.
* `void va_end(va_list ap);`

### B.8 Non-local Jumps `<setjmp.h>`
* `int setjmp(jmp_buf env)` : save state information in `env`
* `void longjmp(jmp_buf env, int val)` : restore the state saved in `env`

### B.9 Signals `<signal.h>`
Functions to handle exceptional conditions that arises during execution.

### B.10 Date and Time Functions `<time.h>`
`clock_t` and `time_t` are **arithmetic** types representing times. `struct tm`
holds many fields representing a calendar time (hour, minutes, seconds, day,
month, year...).

Common functions :
* `clock_t clock(void)` : return processor ticks used by the program since
  beginning of execution. `clock()/CLOCKS_PER_SEC` is a time in seconds.
* `time_t time(time_t *tp)` : return current calendar time.
* `double difftime(time_t t2, time_t t1)` : return `t2-t1` in seconds.
* `size_t strftime(char *s, size_t smax, const char *fmt, const struct tm *tp)`
  : format date and time of `tp` according to `fmt` into `s`. At most `smax`
  characters are written. `fmt` can uses `%H, %M, %S, %m, %y, %W...`.

### B.11 Implementation-defined Limits `<limits.h>` and `<float.h>`
The first one contains constants representing the range of integral basic types
(`LONG_MAX, SHRT_MIN, ULONG_MAX, CHAR_MIN...`).

The second one contains constants related to floating-point arithmetic
(`FLT_DIG, FLT_EPSILON, DBL_MIN, ...`).

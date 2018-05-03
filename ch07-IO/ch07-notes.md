The C programming language (K&R, 2nd edition)
=============================================

Chapter 7 : Input and Output
----------------------------

### 7.1 Standard Input and Output
`int getchar(void)` : read one character (or EOF, defined in `<stdio.h>`) from
_standard input_.

`int putchar(int c)` : puts the character c on the _standard output_, returns
the character written or EOF if error occurred.

`printf()` also write characters to _standard output_. Each programs that uses
input/output functions must contain `#include <stdio.h>`.

Standard input can also comes from a file (`./a.out < file`) or other programs
(`./prog1 | ./prog2`). The same goes for standard output (`./a.out > file`).

### 7.2 Formatted Output - Printf
`int printf(char *format, arg1, arg2, ...)` : convert, format and print its
arguments. Return number of characters printed. The format string can contain
conversion specifications characters `%...` :
* i, d : `int`
* o : `int`, unsigned octal number
* x, X : `int`, unsigned hexadecimal number, using "abcdef" or "ABCDEF"
* s : `char *`
* p : `void *`, pointer

Printing "hello, world" (12 char) :
* `%s        ->  "hello, world"`
* `%10s      ->  "hello, world"` (at least 10 char printed)
* `%.10s     ->  "hello, wor"` (at most 10 char printed = precision)
* `-15.10%s  ->  "hello, wor     "` (left aligned because of "-", at least 15
  char wide, at most 10 char from string printed)

`int sprintf(char *string, char *format, arg1, arg2, ...)` : format arguments
according to _format_, but store result in _string_ instead of standard output.
_string_ must be large enough to store formatted result.

### 7.3 Variable-length Argument Lists
Use `...` as the last argument to indicate the number and types of functions
arguments may vary (`void minprintf(char *format, ...)`.

The _unamed_ arguments are stored in a list, accessed with a moving pointer `ap`
of type `va_list`. Initialization wih `va_start`, moved with `va_arg`.
```C
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unamed arg in turns */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* make ap point to first unamed arg */
    for (p = fmt; *p; ++p)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        switch(*++p)
        {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; svam++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap)
```

### 7.4 Formatted Input - Scanf
`int scanf(char *format, ...)` : read characters from _standard input_, convert
and store result in argument list **pointers**. Return EOF or number of
converted values.

There is also the function `sscanf(char *s, char *format, ...)` which reads from
_string_ instead of _standard input_.

The string _format_ indicates how the conversion should be done :
* `%d, %i` : convert to `int`
* `%u` : convert to `unsigned int`
* `%s` : convert to character string
* `%f, %e, %g` : convert to `float/double`

Sometime there is `l` or `u` right after the `%` for `long` or `short` integers
(`scanf("%lf", &v)`).

* `25 Dec 1988 : char monthname[20]; scanf("%d %s %d", &day, monthname, &year);`
* `mm/dd/yy : scanf("%d/%d/%d", &month, %day, &year);`

`scanf()` skips whites spaces (including newlines) to read new input values.

### 7.5 File Access
The function `fopen()` takes the name of a file an return a **pointer to FILE**.
FILE is a type name (defined with `typedef`).
```C
FILE *fp;

/* mode can be r (read), w (write), a (append) and optional b (binary) */
FILE *fopen(char *name, char *mode);
fp = fopen(name, mode);
```

Opening a non-existing file for writing/appending creates it. Writing to
existing file _overwrite_ its content. If an error occurs in `fopen()`, it
returns a `NULL` pointer. Once file is opened :
* `int getc(FILE *fp)` : return next character from fp, or EOF.
* `int putc(int c, FILE *fp)` : write character c, return it or EOF if error
  occurred

When program is started, OS opens 3 files and provides pointers to them :
`stdin/stdout/stderr` (so `getchar()` can be written as `getc(stdin)`).

`fscanf(FILE *fp, char *fmt, ...)` and `fprintf(FILE *fp, char *fmt, ...)` :
same as `scanf` and `printf` but read from file instead of _stdin_.

`int fclose(FILE *fp)` : close the file, free pointer fp so it can be reuse to
open another file. Closing an output file also **flushes the putch() buffer**.
Files are automatically closed when program exits without errors.

### 7.6 Error Handling - Stderr and Exit
**stderr** is an output stream (opened by OS when program starts), that appears
on the screen, even if **stdout** is redirected to another file/program.

To signal errors :
* `fprintf(stderr, "error message")`
* `exit(1), exit(2)` : terminates program. Argument can be used by the process
  that called the program. `exit()` closes each opened file to flush buffers.

Within _main_, `return expr <=> exit(expr)`. `int ferror(FILE *fp)` returns
non-zero value if an error occurred on stream fp. `feof(FILE *fp)` is the same,
but returns non-zero value if end of file occurred on fp.

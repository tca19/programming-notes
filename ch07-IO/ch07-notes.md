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
* `%.10s     ->  "hello, wor" (at most 10 char printed = precision)
* `-15.10%s  ->  "hello, wor     " (left align because of "-", at least 15 char
  wide, at most 10 char from string printed)

`int sprintf(char *string, char *format, arg1, arg2, ...)` : format arguments
according to _format_, but store result in _string_ instead of standard output.
_string_ must be large enough to store formatted result.

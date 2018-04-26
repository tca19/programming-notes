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

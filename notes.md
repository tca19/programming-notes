The C programming language (K&R, 2nd edition)
=============================================

Preface
-------
ANSI = American National Standard Institute, created in 1983 (and finished in
1988) "_an unambiguous and machine-independant definition of the language C_".

This book describes the C programming language **as defined by the ANSI
standard** (standard structure assignment and enumerations, new function
declaration, standard library).

C is not tied to any particular hardware or system. C has been used to write the
OS, the C compiler and many UNIX applications programs.

Introduction
------------
C is a general-purpose programming language, mostly used to write compilers, OS
and system programs. C has types :
  * characters
  * integers
  * floating-point numbers
  * pointers
  * arrays
  * structures

C is a _low level_ languages because it deals with the same sort objects as
computers (characters, numbers, adresses, operators). C has no native
multithread support (need an additional library for that).

Chapter 1 : A Tutorial Introduction
-----------------------------------

### 1.1 Getting started
The classic "hello, world" :
```C
#include <stdio.h>

main()
{
    printf("hello, world\n);
}
```
Needs to compile with the `-ansi` flag, otherwise the compiler warns us that
main() needs to explicitly return an int.

Function arguments = one way to communicate data between functions.

"hello, world\n" = a sequence of characters in double quotes "", named
**character string**.

Special characters :
  * `\n` (newline)
  * `\t` (tab)
  * `\b` (backspace)
  * `\"` (double quotes)
  * `\\` (backslash)
  * `\r` (carriage return)

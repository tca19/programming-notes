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

`"hello, world\n"` = a sequence of characters in double quotes "", named
**character string**.

Special characters :
  * `\n` (newline)
  * `\t` (tab)
  * `\b` (backspace)
  * `\"` (double quotes)
  * `\\` (backslash)
  * `\r` (carriage return)

### 1.2 Variables and Arithmetic Expressions
`/* */` are used to make comments. In C all variables need to be **declared
before they are used** (like in `fahrenheit.c`, L 7-8) :

```C
int fahr, celsius;
int lower, upper, step;
```

After the declaration, we initialize the value of these variables with
**assignment statements** : `lower = 0;`.

In a `while()` loop, the condition in `()` is evaluated. If it is true, the
statements in the body of the loop are executed. Else, the code moves to the end
of the loop and continue to execute following statements.

In C, with integer values, `5/9` is `0`, so we first multiply `(fahr-32)` by
`5`, **then** divide by `9`.

The `printf()` function is not a part of the C language, but a function from a
library, _defined by the ANSI standard_, so the behavior is the same for every
compiler that conforms to the standard.

```C
"%3.0f" -> at least 3 characters wide, no decimal point, float number
"%6.1f" -> at least 6 characters wide, 1 decimal point, float number
"%o"    -> octal representation
"%x"    -> hexadecimal representation
"%c"    -> character
```

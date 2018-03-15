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

### 1.3 The For Statement
The `for` loop is a generalization of the `while` loop. It contains 3 parts :
**initialization**, **condition** and **incrementation**.

`for(fahr = 0; fahr <= 300; fahr = fahr + 20)`

### 1.4 Symbolic Constants
_Symbolic name (or symbolic constant)_ :
```C
#define name replacement_text
```
They are not variables, so no type. Usually in UPPERCASE.

### 1.5 Character Input and Output
C deals with **streams of characters (text stream)**. Two main functions :
  * `c = getchar()` : reads next input character from a text stream
  * `putchar(c)` : print the character `c`.

`getchar()` returns a special value when there is no more input : **EOF**
(different from any char value, equal to -1 on my machine). So we need to
declare `c` as an `int` to be able to handle this value.

We can use assignment in a condition :
```C
/* precedence of != is higher than that of =, so without extra parentheses,
   condition is evaluated as c = (getchar() != EOF) */
while ((c = getchar()) != EOF)
    putchar()
```

When counting words or characters, use a long variables : `long nc;` (because it
can holds larger values, some architectures limit `int` to 16 bits, so 32767 is
maximum value). Then use `printf("%ld\n", nc)` to print it.

Since the condition in a `while()` or a `for()` loop is evaluated
**before** entering the loop, the code returns 0 when there is no input.

A line is terminated by a `\n` character so to count number of lines, simply
count the number of `\n`. A character written between single quotes like `'\n'`
represents an integer value equal (10) to the numerical value of the character
in the machine's character set, called an **character constant**. Just another
way to write a small integer, so `'A'` is 65.

A word is any sequence of characters that does not contain a blank, tab or
newline. To count words :
  * initialize a state variable to OUT
  * increment a counter nw each time there is a non-blank character and state is
    OUT. Set state to IN
  * each time there is a blank character, set state to OUT

We can initialize multiple variables at once with `nl = nw = nc = 0`.  In a long
boolean expression, passive evaluation is applied so it stops to evaluate once
it knows the final boolean value.

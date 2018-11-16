The C programming language (K&R, 2nd edition)
=============================================

Preface
-------
C was designed to be the language of the UNIX system.

ANSI = American National Standard Institute, created in 1983 (and finished in
1988) "_an unambiguous and machine-independant definition of the language C_".
ANSI established a modern version of C, for machine independency.

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

**Ken Thompson** wrote language B in 1970 for UNIX systems. **Dennis Ritchie**
wrote language C between 1969 and 1973. C is a _low level_ languages because it
deals with the same sort of objects as computers (characters, numbers, adresses,
operators, pointer arithmetic). No heap or garbage collection. C is not a big
language (only a few keywords) and you have to call functions for some things
you would have thought they were builtin (read/write file, string comparison...
). C has no native multithread support (need an additional library for that).

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

Every program **must have** a main somewhere. A C program contains functions and
variable. Functions contain statement and variables to store values used for
computation.

Function arguments = one way to communicate data between functions.

`"hello, world\n"` = a sequence of characters in double quotes "", named
**character string**.

Special characters :
  * `\n` (newline)
  * `\t` (tab)
  * `\b` (backspace)
  * `\"` (double quotes)
  * `\\` (backslash)
  * `\r` (carriage return, move back cursor at position 0)

### 1.2 Variables and Arithmetic Expressions
`/* */` are used to make comments. In C all variables need to be **declared
before they are used** (like in `fahrenheit.c`, L 7-8) :

```C
/* declaration = type name + list of variables */
int fahr, celsius;
int lower, upper, step;
```

After the declaration, we initialize the value of these variables with
**assignment statements** : `lower = 0;`.

In a `while()` loop, the condition in `()` is evaluated everytime. If it is
true, the statements in the body of the loop are executed. Else, the code moves
to the end of the loop and continue to execute following statements.

In C, with integer values, `5/9` is `0`, so we first multiply `(fahr-32)` by
`5`, **then** divide by `9` : `celsius = 5 * (fahr-32) / 9;`.

The `printf()` function is not a part of the C language, but a function from a
library, _defined by the ANSI standard_, so the behavior is the same for every
compiler that conforms to the standard.

```C
"%3.0f" -> at least 3 characters wide, no decimal point, float number. Align with spaces if less than 3 characters.
"%6.1f" -> at least 6 characters wide, 1 decimal point, float number. Add spaces if size is less than 6.
"%o"    -> octal representation
"%x"    -> hexadecimal representation
"%c"    -> character
```
You can use directly `(5.0/9.0)*(fahr-32.0)` in `printf()`.

### 1.3 The For Statement
The `for` loop is a generalization of the `while` loop. It contains 3 parts :
**initialization** (done once at the beginning), **condition** and
**incrementation**.

`for(fahr = 0; fahr <= 300; fahr = fahr + 20)`

### 1.4 Symbolic Constants
_Symbolic name (or symbolic constant)_ :
```C
#define name replacement_text
```
They are not variables, so no type. Usually in UPPERCASE. They replace the
*magic numbers*, the numbers in the code without explicit meaning like `300` and
`20` in the `for` loop above.

### 1.5 Character Input and Output
C deals with **streams of characters**. A **text stream** is a sequence of lines
(zero of more characters followed by a newline). Standard library read/write one
char at a time. Two main functions :
  * `c = getchar()` : reads next input character from a text stream
  * `putchar(c)` : print the character `c`.

`getchar()` returns a special value when there is no more input : **EOF**
(different from any char value, equal to -1 on my machine). So we need to
declare `c` as an `int` to be able to handle this value, and also because it can
sometimes return high values, so `char` is not enough.

We can directly use assignment in a condition expression :
```C
/* precedence of != is higher than that of =, so without extra parentheses,
   condition is evaluated as c = (getchar() != EOF), and becomes either c = 0 or
   c = 1. */
while ((c = getchar()) != EOF) /* easier to read, more compact */
    putchar()
```

When counting words or characters, use a long variables : `long nc;` (because it
can holds larger values as some architectures limit `int` to 16 bits, so 32767 is
maximum value). Then use `printf("%ld\n", nc)` to print it. `printf()` uses `%f`
for `float` and `double`.

Since the condition in a `while()` or a `for()` loop is evaluated
**before** entering the loop, the code returns 0 when there is no input.

A line is terminated by a `\n` character, so to count number of lines, simply
count the number of `\n`.

**Character constant** : a character written between single quotes ' '
represents the integer value of this character: `'A'` **IS** `65` (equivalent),
`'\n'` **IS** `10`.

We can initialize multiple variables at once with `nl = nw = nc = 0`.

A word is any sequence of characters that does not contain a blank, tab or
newline. To count words :
  * initialize a state variable to OUT `[1]`
  * increment a counter nw each time there is a non-blank character and state is
    OUT. Set state to IN `[2]`
  * each time there is a blank character, set state to OUT `[3]`

```C
#define IN 1
#define OUT 0

int main(void)
{
    int c, nl, nw, state;
    nl = nw = nc = 0;
    state = OUT; /* [1] */
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n') ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT; /* [3] */
        else if (state == OUT)
        {
            ++nw; /* [2] */
            state = IN;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}
```

In a long boolean expression, passive evaluation is applied so it stops to
evaluate once it knows the final boolean value.

### 1.6 Arrays
To declare an array : `int ndigit[10];`.

We can use character constant to find if a character is a digit and its numeric
value :
```C
if (c >= '0' && c <= '9') /* test if c is a digit */
    ++ndigit[c-'0']; /* count number of occurrences of each digit in string */
```

### 1.7 Functions
A function = equivalent to a subroutine, convenient way to encapsulate some
computations which can be reused.

> With properly designed functions, it is possible to ignore _how_ a job is
> done; knowing _what_ is done is sufficient.

Function definitions are like :
```C
/*
return-type function-name(parameter declaration, if any)
{
    declarations
    statements
}
*/

/* the variable name `base`, `n` are local; another function can use the same */
int power(int base, int n)
{
    /* ... */
}
```

* **parameter** : variable named in the parenthesized list in a function
definition
* **argument** : value used in a call of the function
* **function prototype** : to indicate what is the value returned by a function
  and the type of expected arguments (`int power(int base, int n);`). Introduced
  by ANSI C.

Parameter names are optional in a function prototype, but names provide good
self-documentation.

If a function definition does not agree with its prototype => ERROR.

### 1.8 Arguments - Call by Value
In C, all function arguments are passed by **value** (functions receive a local
copy, not the original variable). So they can directly be used as a variable,
but they can not alter the original variable, only its private temporary copy.

Parameters can be seen as conveniently initialized local variables = more
compact code.

The exceptions is with arrays : it is passed as a **reference**, not a copy (it
is the adress of first cell of array). So a function can directly modify an
array.

### 1.9 Characters Arrays
*Idea*: read stream line by line, test if current line is longer than currently
saved one and save it if so. Then print the longest line. You can easily divide
this program with two functions: `getline` and `copy`.

The function `getline()` needs to return a signal about possible EOF. We can set
it to return the length of the line, or `0` if EOF is encountered (even a blank
line has at least one `\n` character, so a blank line is not considered as EOF).
`0` is perfect because `0` is never a valid line length.

We can declare empty `for` and `while` loop with a semi colon `;` :
```C
for (...)
    ;

while (...)
    ;
```

Function that operates on arrays of characters :
```C
int getline(char s[], int lim) /* int is default return type, can be omitted */
{
    int c, i;
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
```

If a function does not return something that is reused, its type is `void`. In
C, all arrays of characters (**string constant**) are terminated by the `\0`
(_null character_) symbol.

### 1.10 External Variables and Scope
Variables declared in one function are **local** and **private** : no other
functions can access them. Local variables (_automatic variables_) in a function
are created when the function is called but disappears when the function is
exited.

* **Argument**: communicate data between functions.
* **External variables**: declared **once** outside functions, globally
  accessible to all functions. Moreover, they retain their value when a function
  that uses them ends.

```C

/* outside any functions (like a standard variable definition). In general after
the #define. */
int max;
char line[100];

/* inside a function (add `extern` before definition) */
extern int max;
extern char line[];
```
Variables must be declared in function to access it, so either need an explicit
`extern`, or it is implicit from the context. Usually, external variables are
defined at the beginning of the same file, so the`extern` declaration in
function can be omitted. If a variable is used across several files, the
external variable must be defined in a _header file_. **DO NOT** overuse
external variables: data connections are not obvious / program hard to modify.

For compatibility, functions with no arguments should have `void` as their
argument.

* **definition** : where variable is created or assigned storage
* **declaration** : where the nature of the variable is stated but no storage is
  allocated (like in a function argument list)

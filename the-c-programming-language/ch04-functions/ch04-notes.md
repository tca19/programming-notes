The C programming language (K&R, 2nd edition)
=============================================

Chapter 4 : Functions and Program Structure
-------------------------------------------

Functions break large computing tasks into smaller ones, clarifying the whole
program. They allow clearer code (separate things) and reuse of some parts
(instead of recreating everything from scratch). Many small functions are better
than a few big ones.

### 4.1 Basics of Functions
Suppose you want to print every input line that has 'ould' in it. A method could
be:
```
while (there's a line)
    if ('ould' in line)
        print line
```
This program can be split into 3 functions: `getline()`, `strindex(s, t)` and
`print(s)` instead of having a single main().

We want the function `strindex(s, t)` to return the position in the string `s`
where the string `t` begins. So the returned position is positive (it's an array
index). Therefore, `-1` is a _good error code_ to indicate that string `t` is
not found in `s`. Prefer `> 0` to `!= 0`. See implementation in
[grep.c](examples/grep.c).

Each function definition has the form :
```
return_type function_name(argument declarations)
{
    declarations and statements;
}
```
If return type is omitted, `int` is assumed. **Communication between the
functions is by arguments and values returned by the functions**.  If `main()`
returns a status code, it can be used by the environment that called the
program. You can add parentheses in a return statement (`return (2)`) but they
are optional. If a function reaches its closing `}` withtout any `return`, it
returns nothing.

If a program is separated into multiple source files, then `cc main.c getline.c
strindex.c` will compile each file, producing `main.o, getline.o, strindex.o`
then link all `*.o` files to produce `a.out`.

### 4.2 Functions Returning Non-integers
The (true) `atof()` function is declared in `<stdlib.h>`. See an example of
[atof.c](examples/atof.c).

Compiler can not detect mismatch if a function return type is not the same as
used type when the function is in another source file. If in `main` we have `sum
+= atof(val)` and the prototype of `atof` has not been declared yet (first time
the compiler sees it), **the compiler assumes it is a name function and returns
an `int` by default**. So we need to tell `main` that `atof()` returns something
else than an `int`.

```C
int main()
{
    double sum, atof(char []); /* indicate that atof returns a double */
    /* ... */
    printf("\t%g\n", sum += atof(line)); /* add to sum, print sum */
}

double atof(char s[])
{
    ...
}
```
If there is no function prototype, a function is **implicitly declared by its
first appearance** in an expression. If a function does not have an argument
list, as `double function()`, it means that **parameters checking is turned
off**, not that it takes no arguments. Use `f(void)` to declare that a function
`f` does not take any arguments.

### 4.3 External Variables
* External objects: either variables or functions defined in the program,
  _outside_ any functions (potentially available to many functions).
* Internal objects: arguments and variables defined _inside_ functions.

External variables are an alternative to arguments/return values for
communicating data between functions (they have greater scope and lifetime and
retain value). So they can be used to share data between functions.

If we want to build a reverse Polish notation interpreter, we need a stack to
push/pop elements. But `main()` does not have to know and have access to this
stack. The `push()` and `pop()` functions and related external variables and
`#define` **are declared AFTER** the main function so `main()` cannot access
them.

If you don't want an external variable to be accessible to a function, declare
it _after_ this function.

Programs cannot determine if they have read enough input until they have read
too much. So they read characters with `getch()`, and when they have read too
much, they un-read it with `ungetch()` (in fact, it puts the character into a
buffer, and each call to `getch()` first check the buffer before reading input).
```C
#define BUFSIZE 100

char buf[BUFSIZE];     /* char array buffer, shared by getch/ungetch */
int bufp = 0;          /* next free position in buf */

/* getch: read the next input char from the buffer. If empty, read getchar() */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: puch the c character back into the buffer input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
```
Original `ungetc()` only stores 1 `char` (not a whole stack).

### 4.4 Scope Rules
Functions are external variables because they are not declared inside functions.

External variables and functions of a C program are not all compiled at the same
time: some are in different files, some are precompiled in libraries.

* scope of a name : part of a program within the name can be used.
  Parameters of a function are local variables (because they are passed by value
  and are copies of original) and can only be used in this function.
* scope external variables/functions : from where it is declared to the end of the
  file compiled. In the [reverse_polish.c](examples/reverse_polish.c) calculator
  program, `sp` and `val` were accessible to `pop()` and `push()` but not to
  `main()` because they were defined **AFTER**.

* `int sp;`: a **definition**, storage is set aside.
* `extern int sp;` a **declaration**, only announces the type and name of
`sp`, do not create the variable or reserve storage for it.

Only 1 definition for external variables among all the files of the program.
Array size are obligatory in definitions but not in declarations.

### 4.5 Header Files
If we want to separate our reverse Polish calculator into several files, we
would create :
* `main.c`
* `stack.c` (for `push/pop` and their variables)
* `getop.c`
* `getch.c` (most likely to come from a library)

Header files are here to **centralize declarations/definitions of shared
variables** (easier to manage). Up to a certain point, it is better to have only 1 header file
where everything is centralized (in this case, `calc.h`).

```C
/* calc.h */
#define NUMBER '0'
void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);

/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXOP 100
main(void)
{
  ...
}

/* getop.c */
#include <stdio.h>
#include <ctype.h>
#include "calc.h"
getop(char[] s)
{
  ...
}

/* stack.c */
#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];
void push(double v) { ... };
double pop(void) { ... };
```

In each `.c` file, there is the line `#include "calc.h"`.

### 4.6 Static Variables
The prefix `static` added to an external variable or function limits its scope to
the rest of that source file.
```C
/* no functions in other files will be able to access these variables */
static char buf[BUFSIZE];
static int bufp = 0;
```

Normally, function names are **global**, visible to any part of the entire
program.  If we add `static` in front of a function name, it **becomes invisible
outside the file** in which it is declared.

If a variable inside a function is declared `static`, it remains in existence
between each call. So they provide a **private, permanent storage** inside a
function.

### 4.7 Register Variables
`register int x;` : indicate to the compiler that the variable will be used a
lot so it might be a good idea to put it in register. Compilers can ignore this
indication. Can only be used on _automatic variables_ and _formal parameters of
a function_ (`f(register unsigned x, register char n)`.

It is **not possible to take the address of a register** variable.

### 4.8 Block Structure
We can declare variables inside the block of a compound statement. In this case,
the scope of these variables is that block (they remain in existence until the
final `}` of the block).

Variables declared inside a block **hide** external variables which have the
same name.
```C
int x;
int y;

f(double x)
{
    double y;

    /* any reference to x or y is a double, not an int */
    ...
}
```

### 4.9 Initialization
Without explicit initialization, **external and static** variables are
**guaranteed to be initialized to 0**. Automatic and register variables have
_undefined_ initial values. We can initialize when we define variables : `long
day = 1000L * 60L * 60L * 24L;`.

External and static variables **must** be initialized with _constant
expression_.

When initializing an array (`int ar[10] = {1, 2, 3}`), if there are fewer
initializers than the specified size, missing values are set to `0`.

We can directly initialize char arrays with a string :
```C
char pattern = "ould";
/* equivalent to char pattern = { 'o', 'u', 'l', 'd', '\0' }; */
```

### 4.10 Recursion
**Recursion** : when a function calls itself.
```C
#include <stdio.h>

/* printd: print n in decimal. Start by printing leading digits */
void printd(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd(n / 10);
    putchar(n % 10 + '0');
}
```
Another common recursion example is `quicksort(int [], int, int)` (choose pivot,
create subarrays of elements less/greater than pivot, sort these subarrays).

### 4.11 The C Preprocessor
Two main commands :
1. `#include`

   Any line like `#include "filename"` or `#include <filename>` is replaced by
   the content of the file _filename_. Usually we use `"..."` to  search for
   files in the same working directory. When an included file is changed, it
   needs to be recompiled.

2. `#define` (called _Macro Substitution_)

   `#define name replacement-text` : each occurrence of _name_ token will be
   replaced by _replacement-text_. _replacement-text_ can be written on several
   lines with `\` at the end of each line. Replacement **does not take place in
   quoted strings**.

   `#define max(A, B) ((A) > (B) ? (A) : (B))` : use arguments in macros. No
   data type restriction (works for any data type in A and B). Most of the
   functions in `<stdio.h>` or `<ctype.h>` are implemented as macros, to avoid
   the run-time overhead of a function call.

   A parameter name in the replacement text preceded by `#` is expanded into a
   quoted string with the parameter replaced by the actual argument.
   ```C
   #define dprint(expr) printf(#expr " = %d\n", expr)
   ```
